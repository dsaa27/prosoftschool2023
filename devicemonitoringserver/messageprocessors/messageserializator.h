#ifndef MESSAGESERIALIZATOR_H
#define MESSAGESERIALIZATOR_H
#include "message/errormessage.h"
#include "message/commandmessage.h"
#include "message/meteragemessage.h"
#include <string>
#include <sstream>
#include <vector>
namespace MessageSerializator
{
    std::string serializeMessage(const MeterageMessage& message);
    std::string serializeMessage(const CommandMessage& message);
    std::string serializeMessage(const ErrorMessage& message);
    ErrorMessage deserializeErrorMessage(const std::string& message);
    CommandMessage deserializeCommandMessage(const std::string& message);
    MeterageMessage deserializeMeterageMessage(const std::string& message);
    Message::MessageType identifySerializedMessageType(const std::string& message);
};

#endif
