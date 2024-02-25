#ifndef MESSAGESERIALIZATOR_H
#define MESSAGESERIALIZATOR_H
#include "message/errormessage.h"
#include "message/commandmessage.h"
#include "message/meteragemessage.h"
#include <string>
#include <sstream>
#include <vector>
class MessageSerializator
{
public:
    static std::string serializeMessage(const Message& message);
    static ErrorMessage deserializeErrorMessage(const std::string& message);
    static CommandMessage deserializeCommandMessage(const std::string& message);
    static MeterageMessage deserializeMeterageMessage(const std::string& message);
    static Message::MessageType identifySerializedMessageType(const std::string& message);

private:
    static std::vector<std::string> splitMessageString(const std::string& message);
};

#endif
