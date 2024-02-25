#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H
#include <map>
#include "deviceworkschedule.h"
#include "messageprocessors/messageserializator.h"
#include "encodingmodule.h"

class CommandCenter
{
public:
    std::string processMessage(const std::string& message, const EncodingModule& encoder, uint64_t deviceID);
    double getSTD(uint64_t deviceID);
    void setDeviceWorkSchedule(uint64_t deviceID, DeviceWorkSchedule schedule);
    void reset();

private:
    void updateDeviceSTD(char newError, uint64_t deviceID);
    std::map <uint64_t, std::pair<double, uint64_t>> m_STDArchive;
    std::map<uint64_t, DeviceWorkSchedule> m_devicesWorkScheduleArchive;
    uint64_t m_lastTimeStamp = 0;
};
#endif
