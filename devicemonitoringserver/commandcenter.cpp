#include "commandcenter.h"

uint64_t CommandCenter::m_lastTimeStamp = 0;
std::map<uint64_t, std::pair<double, uint64_t>> CommandCenter::m_STDArchive;
std::map<uint64_t, DeviceWorkSchedule> CommandCenter::m_devicesWorkScheduleArchive;

std::string CommandCenter::processMessage(const std::string& message, const EncodingModule& encoder, uint64_t deviceID)
{
    auto meterage = MessageSerializator::deserializeMeterageMessage(encoder.decode(message)).getMeterage();
    if (meterage.first < m_lastTimeStamp)
    {
        return encoder.encode(
        MessageSerializator::serializeMessage(ErrorMessage(ErrorMessage::ErrorType::Obsolete)));
    }
    m_lastTimeStamp = meterage.first;
    if (m_devicesWorkScheduleArchive.find(deviceID) == m_devicesWorkScheduleArchive.end() 
        || m_devicesWorkScheduleArchive[deviceID].schedule.empty())
    {
        return encoder.encode(
        MessageSerializator::serializeMessage(ErrorMessage(ErrorMessage::ErrorType::NoSchedule)));
    }

    uint64_t i = 0;
    auto schedule = m_devicesWorkScheduleArchive[deviceID].schedule;
    while (i < schedule.size() && schedule[i].timeStamp <= meterage.first) {++i;}
    if (!i)
    {
        return encoder.encode(
        MessageSerializator::serializeMessage(ErrorMessage(ErrorMessage::ErrorType::NoTimestamp)));
    }
    uint64_t index = i == schedule.size() - 1 && meterage.first >= schedule[i].timeStamp ? i : i - 1;
    char error = schedule[index].value - meterage.second;
    updateDeviceSTD(error, deviceID);
    return encoder.encode(MessageSerializator::serializeMessage(CommandMessage(error)));
}

double CommandCenter::getSTD(uint64_t deviceID)
{
    return std::sqrt(m_STDArchive[deviceID].first / m_STDArchive[deviceID].second);
}

void CommandCenter::setDeviceWorkSchedule(uint64_t deviceID, DeviceWorkSchedule schedule)
{
    m_devicesWorkScheduleArchive[deviceID] = schedule;
}

void CommandCenter::reset()
{
    m_lastTimeStamp = 0;
    m_STDArchive.clear();
    m_devicesWorkScheduleArchive.clear();
}

void CommandCenter::updateDeviceSTD(char newError, uint64_t deviceID)
{
    if (m_STDArchive.find(deviceID) == m_STDArchive.end())
    {
        m_STDArchive.emplace(deviceID, std::pair<double, uint64_t>(0, 0));
    }
    m_STDArchive[deviceID].first += newError * newError;
    ++m_STDArchive[deviceID].second;
}
