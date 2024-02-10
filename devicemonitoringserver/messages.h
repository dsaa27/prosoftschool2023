#ifndef MESSAGES_H
#define MESSAGES_H

#include "deviceworkschedule.h"
#include <cstdint>

enum class MsgType : uint8_t {Meterage, Command, Error, None};
enum class ErrType : uint8_t {NoSchedule, NoTimestamp, Obsolete, NoErr};

struct MessageBase
{
    // MessageBase() = default;
    MsgType MessageType = MsgType::None;/* data */
    Phase data = {0,0};
    ErrType error = ErrType::NoErr;
    int8_t correction = 0;
};

// struct MessageError : MessageBase
// {
//     // MessageError() = default;
//     ErrType error = ErrType::NoErr;
// };

// struct MessageMetric : MessageBase
// {
//     // MessageMetric() = default;
//     Phase data = {0,0};
// };

// struct MessageCommand : MessageBase
// {
//     // MessageCommand() = default;
//     int8_t correction = 0;
// };


#endif

