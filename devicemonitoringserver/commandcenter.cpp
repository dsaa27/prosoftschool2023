#include "commandcenter.h"
#include "preparingmessage.h"

#include <numeric>
#include <cmath>

void CommandCenter::addDeviceWorkSchedule(const pDeviceWorkSchedule& newDeviceWorkSchedule)
{
	m_DeviceWorkSchedules.insert(pDeviceWorkSchedule(newDeviceWorkSchedule));
}

int8_t CommandCenter::getPlannedMeterage(const pMeterage& meterage, const pDeviceWorkSchedule& deviceWorkSchedule) const
{
	uint64_t curTimeStamp = meterage->getTimeStamp();
	for (auto phase : deviceWorkSchedule->schedule)
	{
		if (phase.timeStamp == curTimeStamp)
		{
			return phase.value;
		}
	}
	return -1;
}

float CommandCenter::calculateMeanSquaredDeviation(const uint64_t& deviceId)
{
	uint8_t countMeterage = m_DevicesInfo[deviceId].m_meterages.size();
	std::vector<uint8_t> meterages = m_DevicesInfo[deviceId].m_meterages;
	uint64_t sum = std::accumulate(meterages.begin(),meterages.end(), 0);
	float averageValue = float(sum) / countMeterage;

	float meanSquaredDeviation = 0;

	for(const auto meterage : m_DevicesInfo[deviceId].m_meterages)
	{
		meanSquaredDeviation += std::pow(meterage - averageValue, 2);
	}

	return std::sqrt(meanSquaredDeviation/ countMeterage);

}

int8_t CommandCenter::calculateAdjustment(const pMeterage& meterage, const uint8_t& plannedMeterage) const
{
	return plannedMeterage - meterage->getMeterage();
}

std::map<uint64_t, DeviceInfo> CommandCenter::getDevicesInfo() const
{
	return m_DevicesInfo;
}

std::set<pDeviceWorkSchedule> CommandCenter::getDeviceWorkSchedules() const
{
	return m_DeviceWorkSchedules;
}

void CommandCenter::updateMeterageHistory(const pMeterage& meterage, const uint64_t& deviceId)
{
	m_DevicesInfo[deviceId].m_meterages.push_back(meterage->getMeterage());
}

bool CommandCenter::checkValidityTimeStamp(const pMeterage& meterage, const uint64_t& deviceId)
{
	return (meterage->getTimeStamp() == m_DevicesInfo[deviceId].m_meterages.size());
}

pDeviceWorkSchedule CommandCenter::getDeviceWorkSchedule(const uint64_t& deviceId) const
{
	for (pDeviceWorkSchedule deviceWorkSchedule : m_DeviceWorkSchedules)
	{
		if (deviceWorkSchedule->deviceId == deviceId)
		{
			return deviceWorkSchedule;
		}
	}
	return nullptr;
}

std::string CommandCenter::processMessage(const std::string& message, const uint64_t& deviceId)
{
	pMeterage meterage =
		std::static_pointer_cast<Meterage>(preparingmessages::depackMessage(message));
	if (!checkValidityTimeStamp(meterage, deviceId))
	{
		Error error(ErrorType::Obsolete);
		return preparingmessages::packMessage(error);
	}

	updateMeterageHistory(meterage, deviceId);


	pDeviceWorkSchedule deviceWorkSchedule = getDeviceWorkSchedule(deviceId);
	if (!deviceWorkSchedule)
	{
		Error error(ErrorType::NoSchedule);
		return preparingmessages::packMessage(error);
	}

	int8_t planndeMeterage = getPlannedMeterage(meterage, deviceWorkSchedule);
	if (planndeMeterage == -1)
	{
		Error error(ErrorType::NoTimestamp);
		return preparingmessages::packMessage(error);
	}

	uint64_t timeStamp = meterage->getTimeStamp();
	std::map<uint64_t, float> &msd = m_DevicesInfo[deviceId].m_MeanSquaredDeviation;
	msd[timeStamp] = calculateMeanSquaredDeviation(deviceId);

	Command command(calculateAdjustment(meterage, planndeMeterage));
	return preparingmessages::packMessage(command);
}
