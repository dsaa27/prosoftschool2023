
#include "commandCenter.h"
#include "../deviceworkschedule.h"

// #include <find>
#include <cmath>
#include <cstdint>
#include <utility>


MessageBase CommandCenter::acceptMessage(uint64_t deviceId, 
                                         const MessageBase& messageStruct) {
    MessageBase messageOut = {MsgType::None, {0,0}, ErrType::NoErr, 0};

    if (mapOfDevices.find(deviceId) == mapOfDevices.end()) { //probbaly not neccesary check of device existance in com center
        DeviceWorkSchedule newDevSchedule;
        newDevSchedule.deviceId = deviceId;
        addDevice(newDevSchedule); // so - add new device with empty schedule
        
        mapOfDevices[deviceId]->lastValidTime = messageStruct.data.timeStamp;
        //so answer here is obviously Error - NoSchedule. 
        messageOut.MessageType = MsgType::Error;
        messageOut.error = ErrType::NoSchedule;
        return messageOut;
    }

    DeviceInfo *device = mapOfDevices[deviceId];
    if (device->devWorkSched.schedule.empty()) {
        messageOut.MessageType = MsgType::Error;
        messageOut.error = ErrType::NoSchedule;
        device->lastValidTime = messageStruct.data.timeStamp;                            
        return messageOut;
    }

    if (device->lastValidTime > messageStruct.data.timeStamp) {
        messageOut.MessageType = MsgType::Error;
        messageOut.error = ErrType::Obsolete;
        return messageOut;
    }

    for (u_int i = device->lastValidIndex; i < device->devWorkSched.schedule.size(); ++i) { //for known schedule can check up from last index
        if (device->devWorkSched.schedule[i].timeStamp == 
            messageStruct.data.timeStamp) {
                //got matching line in schedule - responsing correction;
                device->lastValidIndex = i;
                device->lastValidTime = messageStruct.data.timeStamp; 
                messageOut.correction = device->devWorkSched.schedule[i].value - messageStruct.data.value;
                messageOut.MessageType = MsgType::Command;
                messageOut.error = ErrType::NoErr;
                return messageOut;
            }
    }
    device->lastValidTime = messageStruct.data.timeStamp;
    messageOut.MessageType = MsgType::Error;
    messageOut.error = ErrType::NoTimestamp;
    return messageOut;
}

bool CommandCenter::addDevice(DeviceWorkSchedule& newDevSchedule) {
    if (mapOfDevices.find(newDevSchedule.deviceId) != mapOfDevices.end()) return false; //do not changing existing device
    DeviceInfo *newDevice = new DeviceInfo();
    newDevice->devWorkSched = newDevSchedule;
    newDevice->lastValidIndex = 0;
    newDevice->lastValidTime = 0;
    mapOfDevices.insert({newDevSchedule.deviceId, newDevice});
    return true;
}

bool CommandCenter::removeDevice(uint64_t deviceId) {
    if (mapOfDevices.find(deviceId) == mapOfDevices.end()) return false; //nothing to remove

    if ((mapOfDevices.at(deviceId)) != nullptr) 
        //delete (mapOfDevices.at(deviceId)->devWorkSched);
        delete (mapOfDevices.at(deviceId));
    mapOfDevices.erase(deviceId);
    return true;
}

bool CommandCenter::changeSchedule(DeviceWorkSchedule& newDevSchedule) { //in case it is somehow needed
    if (mapOfDevices.find(newDevSchedule.deviceId) == mapOfDevices.end()) return false; //no such device
    mapOfDevices.at(newDevSchedule.deviceId)->devWorkSched = newDevSchedule; //should we delete previous schedule explicitly
    return true;
}

double CommandCenter::getRMSD(uint64_t deviceId, uint8_t newValue) {
    uint64_t currentSumValue = 0;
    DeviceInfo *device = mapOfDevices[deviceId];
    double quadDiffSum = 0;
    for (u_long i = 0; i < device->Phase_Log.size(); ++i) {
        currentSumValue += device->Phase_Log[i].value;
    }

    double meanValue = ((currentSumValue) / device->Phase_Log.size());

    for (u_long i = 0; i < device->Phase_Log.size(); ++i) {
        quadDiffSum += std::pow(meanValue - newValue, 2);
    }
    
    
    double RSMD = std::sqrt(quadDiffSum/meanValue);
    return RSMD;
}
