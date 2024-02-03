#ifndef MESSAGES_H
#define MESSAGES_H

#include "deviceworkschedule.h"

enum class MsgType{Meterage, Command, Error};
enum class ErrType{NoSchedule, NoTimestamp, Obsolete, NoErr};

struct MessageBase
{
    // MessageBase() = default;
    MsgType MessageType;/* data */
};

struct MessageError : MessageBase
{
    // MessageError() = default;
    ErrType error = ErrType::NoErr;
};

struct MessageMetric : MessageBase
{
    // MessageMetric() = default;
    Phase data = {0,0};
};

struct MessageCommand : MessageBase
{
    // MessageCommand() = default;
    int8_t correction = 0;
};


#endif

