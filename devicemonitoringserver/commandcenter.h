#include "deviceworkschedule.h"
#include "messages.h"
#include <vector>
#include <unordered_map>
#include <cstdint>
#include <utility>
#include <limits>


// This struct allows to store start time stamp of the period and its sko
struct SKO {
    uint64_t timeStamp;
     uint8_t sko;
};


class commandCenter {
public:

    bool addDeviceWorkSchedule(DeviceWorkSchedule schedule);
    std::pair<messageType, void*> getNewMessage(uint64_t deviceId, uint64_t timeStamp, uint8_t measure);
    std::unordered_map<uint64_t, std::vector<SKO>> getSKOData() const;

private:
    int findSchedule(uint64_t deviceId);
    uint8_t findMeasurementAtTimeStamp(int scheduleIndex, uint64_t timeStamp);
    
private:
    std::vector<DeviceWorkSchedule> schedules;
    std::unordered_map<uint64_t, uint64_t> prevTimeStamps;
    std::unordered_map<uint64_t, std::vector<SKO>> dataSKO;
};