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
	CommandCenter() = default;
	void addDeviceWorkSchedule(const pDeviceWorkSchedule&);
	std::string processMessage(const std::string&, const uint64_t&);
	std::map<uint64_t, DeviceInfo> getDevicesInfo() const;
	std::set<pDeviceWorkSchedule> getDeviceWorkSchedules() const;

private:
	void updateMeterageHistory(const pMeterage&, const uint64_t&);
	bool checkValidityTimeStamp(const pMeterage&, const uint64_t&);
	pDeviceWorkSchedule getDeviceWorkSchedule(const uint64_t&) const;
	int8_t getPlannedMeterage(const pMeterage&, const pDeviceWorkSchedule&) const;
	float calculateMeanSquaredDeviation(const uint64_t&);
	int8_t calculateAdjustment(const pMeterage&, const uint8_t&) const;

private:
	std::map<uint64_t, DeviceInfo> m_DevicesInfo;
	std::set<pDeviceWorkSchedule> m_DeviceWorkSchedules;
};

#endif // COMMANDCENTER_H
