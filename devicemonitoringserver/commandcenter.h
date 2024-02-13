#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include "deviceworkschedule.h"
#include "messageencoder.h"
#include "messageserializator.h"

#include <map>
#include <set>

struct DeviceInfo
{
	std::vector<uint8_t> m_meterages;
	std::map<uint64_t, float> m_MeanSquaredDeviation;
};



class CommandCenter
{
public:
	void AddDeviceWorkSchedule(const pDeviceWorkSchedule&);
	std::string ProcessMessage(const std::string&, const uint64_t&);

private:
	void UpdateMeterageHistory(const pMeterage&, const uint64_t&);
	bool CheckValidityTimeStamp(const pMeterage&, const uint64_t&);
	pDeviceWorkSchedule GetDeviceWorkSchedule(const uint64_t&);
	int8_t GetPlannedMeterage(const pMeterage&, const pDeviceWorkSchedule&);
	float CalculateMeanSquaredDeviation(const uint64_t&);
	int8_t CalculateAdjustment(const pMeterage&, const uint8_t&);

private:
	std::map<uint64_t, DeviceInfo> m_DevicesInfo;
	std::set<pDeviceWorkSchedule> m_DeviceWorkSchedules;
};

#endif // COMMANDCENTER_H
