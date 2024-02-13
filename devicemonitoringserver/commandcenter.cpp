#include "commandcenter.h"
#include "preparingmessage.h"

#include <numeric>
#include <cmath>

void CommandCenter::AddDeviceWorkSchedule(const pDeviceWorkSchedule& newDeviceWorkSchedule)
{
	m_DeviceWorkSchedules.insert(pDeviceWorkSchedule(newDeviceWorkSchedule));
}

int8_t CommandCenter::GetPlannedMeterage(const pMeterage& meterage, const pDeviceWorkSchedule& deviceWorkSchedule)
{
	uint8_t curTimeStamp = meterage->getTimeStamp();
	for (auto phase : deviceWorkSchedule->schedule)
	{
		if (phase.timeStamp == curTimeStamp)
		{
			return phase.value;
		}
	}
	return -1;
}

float CommandCenter::CalculateMeanSquaredDeviation(const uint64_t& deviceId)
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

int8_t CommandCenter::CalculateAdjustment(const pMeterage& meterage, const uint8_t& plannedMeterage)
{
	return plannedMeterage - meterage->getMeterage();
}

void CommandCenter::UpdateMeterageHistory(const pMeterage& meterage, const uint64_t& deviceId)
{
	m_DevicesInfo[deviceId].m_meterages.push_back(meterage->getMeterage());
}

bool CommandCenter::CheckValidityTimeStamp(const pMeterage& meterage, const uint64_t& deviceId)
{
	if (meterage->getTimeStamp() == m_DevicesInfo[deviceId].m_meterages.size())
	{
		return true;
	}
	return false;
}

pDeviceWorkSchedule CommandCenter::GetDeviceWorkSchedule(const uint64_t& deviceId)
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

std::string CommandCenter::ProcessMessage(const std::string& message, const uint64_t& deviceId)
{
	pMeterage meterage = std::static_pointer_cast<Meterage>(preparingmessages::DepackMessage(message));
	if (!CheckValidityTimeStamp(meterage, deviceId))
	{
		Error error(ErrorType::Obsolete);
		return preparingmessages::PackMessage(error);
	}

	UpdateMeterageHistory(meterage, deviceId);


	pDeviceWorkSchedule deviceWorkSchedule = GetDeviceWorkSchedule(deviceId);
	if (!deviceWorkSchedule)
	{
		Error error(ErrorType::NoSchedule);
		return preparingmessages::PackMessage(error);
	}

	int8_t planndeMeterage = GetPlannedMeterage(meterage, deviceWorkSchedule);
	if (!planndeMeterage)
	{
		Error error(ErrorType::NoTimestamp);
		return preparingmessages::PackMessage(error);
	}

	m_DevicesInfo[deviceId].m_MeanSquaredDeviation[meterage->getTimeStamp()] = CalculateMeanSquaredDeviation(deviceId);

	Command command(CalculateAdjustment(meterage, planndeMeterage));
	return preparingmessages::PackMessage(command);



}




