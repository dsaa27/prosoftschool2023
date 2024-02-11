#ifndef MESSAGES_H
#define MESSAGES_H

#include <cstdint>

enum class messageType { Meterage, Command, Error };
enum class errorType {NoSchedule, NoTimeStamp, Obsolete};

struct meterageMessage {

    meterageMessage(uint64_t timeStamp, uint8_t meterage): 
    _type{messageType::Meterage}, _timeStamp{timeStamp}, _meterage{meterage}
    {}
    ~meterageMessage() = default;

    messageType _type;
    uint64_t _timeStamp;
    uint8_t _meterage;
};

struct commandMessage {

    commandMessage(uint8_t correctCommand): 
    _type{messageType::Command}, _correctCommand{correctCommand}
    {}
    ~commandMessage() = default;

    messageType _type;
    uint8_t _correctCommand;
};


struct errorMessage {

    errorMessage(errorType error): 
    _type{messageType::Error}, _error{error}
    {}
    ~errorMessage() = default;

    messageType _type;
    errorType _error;
};

#endif