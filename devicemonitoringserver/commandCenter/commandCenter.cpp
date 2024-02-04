
#include "commandCenter.h"
#include "../deviceworkschedule.h"

#include <find>

MessageBase CommandCenter::acceptMessage(uint64_t deviceId, 
                                         const MessageBase& messageStruct) {
    
    if (mapOfDevices.find(deviceId) == mapOfDevices.end()) {
        DeviceWorkSchedule emptySchedule;
        addDevice(deviceId);
        changeSchedule(emptySchedule);
        mapOfDevices[deviceId].lastValidTime = messageStruct.data.timeStamp;
        //so answer here is obviously Error - NoSchedule. 
        MessageBase messageOut = {MsgType::Error, 
                                    {0,0}, 
                                    ErrType::NoSchedule, 
                                    0};
        return messageOut;
    }
    DeviceInfo device = mapOfDevices[deviceId];
    if (device.devSchedule.schedule.empty()) {
        MessageBase messageOut = {MsgType::Error, 
                                    {0,0}, 
                                    ErrType::NoSchedule, 
                                    0};
        device.lastValidTime = messageStruct.data.timeStamp;                            
        return messageOut;
    } else {
        if (device.lastValidTime > messageStruct.data.timeStamp) {
            MessageBase messageOut = {MsgType::Error, 
                            {0,0}, 
                            ErrType::Obsolete, 
                            0};
            return messageOut;
        }
        for (long i=device.lastValidIndex; i<device.devSchedule.schedule.size(); ++i) {
            if (device.devSchedule.schedule[i].timeStamp == 
                messageStruct.data.timeStamp) {
                    //got matching line in schedule - responsing correction;
                    device.lastValidIndex = i;
                    device.lastValidTime = messageStruct.data.timeStamp; 
                    MessageBase messageOut = {MsgType::Command, 
                                            {0,0}, 
                                            ErrType::NoErr, 
                                            device.devSchedule.schedule[i].value-messageStruct.data.value};
                    device.RMSD_log.pushBack(getRMSD(deviceId, 
                                                    messageStruct.data.value));
                    return messageOut;
                }
        }
        MessageBase messageOut = {MsgType::Error, 
                                {0,0}, 
                                ErrType::NoTimestamp, 
                                0};
        return messageOut;
        // int pos = std::find(device.devSchedule.schedule.begin(), 
        //                     device.devSchedule.schedule.end(),
        //                     messageStruct.data.timeStamp)
    }
}