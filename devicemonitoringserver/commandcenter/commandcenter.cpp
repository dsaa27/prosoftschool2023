#include "commandcenter.h"

AbstractMessage* CommandCenter::catchMessageFromDevice(uint64_t deviceId, const std::string msgDevice_str_crypted)
{
    AbstractMessage* msg = nullptr;

    // If there is no device with deviceId, create it, but with empty schedule
    if (m_devices.count(deviceId) == 0)
    {
        DeviceWorkSchedule dummySchedule;
        dummySchedule.deviceId = deviceId;
        addDevice(dummySchedule);
    }

    DeviceInfo& device = m_devices[deviceId]; 

    std::string msgDevice_str;
    msgDevice_str = device.crypter.decode(msgDevice_str_crypted);
    
    MeterageMessage* msgDevice = dynamic_cast<MeterageMessage*>(m_serializer.deserialize(msgDevice_str));

    if (device.workSchedule.schedule.empty())
    {
        msg = dynamic_cast<ErrorMessage*>(new ErrorMessage(ErrorMessage::ErrorType::NoSchedule));
        return msg;
    }

    if (device.phaseInfo.currentTimestamp > msgDevice->getTimestamp())
    {
        msg = dynamic_cast<ErrorMessage*>(new ErrorMessage(ErrorMessage::ErrorType::Obsolete));
        return msg;
    }

    for (int i = device.phaseInfo.currentIndex; i < device.workSchedule.schedule.size(); ++i)
    {
        if (device.workSchedule.schedule[i].timeStamp == msgDevice->getTimestamp())
        {
            device.phaseInfo.currentIndex = i;
            device.phaseInfo.currentTimestamp = msgDevice->getTimestamp();
            int8_t deviate = device.workSchedule.schedule[i].value - msgDevice->getMeterage();
            msg = dynamic_cast<CommandMessage*>(new CommandMessage(deviate));
            device.phaseInfo.sumOfSqDiff.push_back(deviate * deviate);
            if (device.phaseInfo.sumOfSqDiff.size() == 0)
            {
                device.phaseInfo.stdDeviation.push_back(0);
            }
            else
            {
                float sum = std::accumulate(device.phaseInfo.sumOfSqDiff.begin(), device.phaseInfo.sumOfSqDiff.end(), 0);
                device.phaseInfo.stdDeviation.push_back(sqrtf(sum / (device.phaseInfo.sumOfSqDiff.size() - 1)));
            }
            return msg;
        }
    }

    msg = dynamic_cast<ErrorMessage*>(new ErrorMessage(ErrorMessage::ErrorType::NoTimestamp));
    return msg;
}

bool CommandCenter::setSchedule(const DeviceWorkSchedule& schedule)
{
    if (m_devices.count(schedule.deviceId) != 0)
        return false;

    m_devices[schedule.deviceId].workSchedule = schedule;
    return true;
}

bool CommandCenter::addDevice(const DeviceWorkSchedule& schedule)
{
    if (m_devices.count(schedule.deviceId) != 0)
        return false;

    DeviceInfo *newDevice = new DeviceInfo();
    newDevice->workSchedule = schedule;
    m_devices[newDevice->workSchedule.deviceId] = *newDevice;
    return true;
}

bool CommandCenter::removeDevice(uint64_t deviceId)
{
    if (m_devices.count(deviceId) != 0)
        return false;

    m_devices.erase(deviceId);
    return true;
}
CommandCenter::DeviceInfo CommandCenter::getDeviceInfo(uint64_t deviceId)
{
    if (m_devices.count(deviceId) == 0)
        return DeviceInfo();
    return m_devices[deviceId];
}

float CommandCenter::getStdDevation(uint64_t deviceId)
{
    return m_devices[deviceId].phaseInfo.stdDeviation.back();
    //if (m_devices.count(deviceId) == 0 || m_devices[deviceId].phaseInfo.stdDeviation.size() < 2)
    //    return 0;
    //std::vector<uint16_t>* stdDev = &m_devices[deviceId].phaseInfo.stdDeviation;
    //uint64_t sum = std::accumulate((*stdDev).begin(), (*stdDev).end(), 0);
    //size_t size = m_devices[deviceId].phaseInfo.stdDeviation.size();
    //return sqrtf(static_cast<float>(sum) / (size - 1));
}