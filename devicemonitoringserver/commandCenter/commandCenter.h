#ifndef COMM_CENTER_H
#define COMM_CENTER_H

#include <map>
#include <vector>
#include "../messages.h"
#include "../deviceworkschedule.h"

struct DeviceInfo {
    
    DeviceWorkSchedule schedule;
    vector<Phase> Log;
    vector<uint16_t> RMSD_log;
};

class CommandCenter {
public:
    CommandCenter() = default;

    MessageBase acceptMessage(uint64_t deviceId, const MessageBase& messageStruct);
    uint16_t getRMSD(uint64_t deviceId);
private:
    std::map<uint64_t, DeviceInfo> mapOfDevices;
};

#endif