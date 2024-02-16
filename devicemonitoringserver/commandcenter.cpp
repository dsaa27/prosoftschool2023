#include "commandcenter.h"
#include <cmath>


int commandCenter::findSchedule(uint64_t deviceId) {
    for (int index = 0; index < schedules.size(); ++index) {
        if (schedules[index].deviceId == deviceId)
            return index;
    }

    return -1;
}

uint8_t commandCenter::findMeasurementAtTimeStamp(int scheduleIndex, uint64_t timeStamp) {
    for (int index = 0; index < schedules[scheduleIndex].schedule.size(); ++index) {
        if (schedules[scheduleIndex].schedule[index].timeStamp == timeStamp)
            return schedules[scheduleIndex].schedule[index].value;
    }

    return std::numeric_limits<uint8_t>::max();
}



bool commandCenter::addDeviceWorkSchedule(DeviceWorkSchedule schedule) {
    if (findSchedule(schedule.deviceId) != -1)
        return false;
        
    schedules.push_back(schedule);
    prevTimeStamps[schedule.deviceId] = std::numeric_limits<uint64_t>::max();
    return true;
}


std::pair<messageType, void*> commandCenter::getNewMessage(uint64_t deviceId, uint64_t timeStamp, uint8_t measure){
    std::pair<messageType, void*> p;
    int scheduleIndex = findSchedule(deviceId);

    // Если мы не имеем нужного плана для данного датчика
    if (scheduleIndex == -1) {
        p.first = messageType::Error;
        errorMessage* msg = new errorMessage(errorType::NoSchedule);
        p.second = reinterpret_cast<void*>(msg);
        return p;
    }

    // Если полученное значение метки времени выходит за пределы области меток времени соотвествующего плана
    if (timeStamp < schedules[scheduleIndex].schedule[0].timeStamp || timeStamp > schedules[scheduleIndex].schedule.back().timeStamp) {
        p.first = messageType::Error;
        errorMessage* msg = new errorMessage(errorType::NoTimeStamp);
        p.second = reinterpret_cast<void*>(msg);
        return p;
    }

    // Елси полученая метка времени меньше ранее полученной для данного датчика
    if (prevTimeStamps[deviceId] != std::numeric_limits<uint64_t>::max() && timeStamp <= prevTimeStamps[deviceId]) {
        p.first = messageType::Error;
        errorMessage* msg = new errorMessage(errorType::Obsolete);
        p.second = reinterpret_cast<void*>(msg);
        return p;
    }

    // Если нет несоотвествий, то можно посылать сообщение с командой
    p.first = messageType::Command;
    int8_t cmd = static_cast<int8_t>(findMeasurementAtTimeStamp(scheduleIndex, timeStamp)) - static_cast<int8_t>(measure);
    commandMessage* msg = new commandMessage(cmd);
    p.second = reinterpret_cast<void*>(msg);


    // Если считать средним значением за период значение измеряемого параметра в плане, то СКО вырождается в простую разность по модулю
    uint8_t currentSko = static_cast<uint8_t>(abs(static_cast<int>(cmd)));
    dataSKO[deviceId].push_back({timeStamp, currentSko});
    
    prevTimeStamps[deviceId] = timeStamp;
    return p;
}

std::unordered_map<uint64_t, std::vector<SKO>> commandCenter::getSKOData() const {
    return dataSKO;
}