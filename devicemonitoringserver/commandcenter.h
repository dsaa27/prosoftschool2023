#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H
#include <map>
#include "deviceworkschedule.h"
#include "messageprocessors/messageserializator.h"
#include "encodingmodule.h"

static class CommandCenter
{
public:
    static std::string processMessage(const std::string& message, const EncodingModule& encoder, uint64_t deviceID);
    static double getSTD(uint64_t deviceID);
    static void setDeviceWorkSchedule(uint64_t deviceID, DeviceWorkSchedule schedule);
    static void reset();

private:
    static void updateDeviceSTD(char newError, uint64_t deviceID);
    static std::map <uint64_t, std::pair<double, uint64_t>> m_STDArchive;
    static std::map<uint64_t, DeviceWorkSchedule> m_devicesWorkScheduleArchive;
    static uint64_t m_lastTimeStamp;
};
#endif
