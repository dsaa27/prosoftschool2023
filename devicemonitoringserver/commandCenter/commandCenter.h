#ifndef COMM_CENTER_H
#define COMM_CENTER_H

#include <map>
#include <vector>
#include <cstdint>
#include "../messages.h"
#include "../deviceworkschedule.h"

struct DeviceInfo {
    
    DeviceWorkSchedule *devWorkSched = nullptr;
    vector<Phase> Phase_Log;
    vector<double> RMSD_log;
    uint64_t lastValidTime = 0;
    uint64_t lastValidIndex = 0;
    
};

class CommandCenter {

public:
    CommandCenter() = default;

    MessageBase acceptMessage(uint64_t deviceId, const MessageBase& messageStruct);
    uint16_t getRMSD(uint64_t deviceId, uint8_t newValue);
    bool addDevice(uint64_t deviceId);
    bool changeSchedule(const DeviceWorkSchedule& newDevSchedule);
    bool removeDevice(uint64_t deviceId);

private:
    std::map<uint64_t, DeviceInfo*> mapOfDevices;
};

#endif