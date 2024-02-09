#include "messageserializator.h"
#include <vector>

std::string MessageSerializator::serializeMessage(const Message& message)
{
    return message.messageToString();
}

ErrorMessage MessageSerializator::deserializeErrorMessage(const std::string& message)
{
    std::vector<std::string> data = MessageSerializator::splitMessageString(message);
    ErrorMessage::ErrorType errorType;
    if (data[1] == "NoSchedule")
    {
        errorType = ErrorMessage::ErrorType::NoSchedule;
    }
    else if (data[1] == "NoTimestamp")
    {
        errorType = ErrorMessage::ErrorType::NoTimestamp;
    }
    else
    {
        errorType = ErrorMessage::ErrorType::Obsolete;
    }
    return ErrorMessage(errorType);
}

CommandMessage MessageSerializator::deserializeCommandMessage(const std::string& message)
{
    std::vector<std::string> data = MessageSerializator::splitMessageString(message);
    return CommandMessage((char)std::stoi(data[1]));
}

MeterageMessage MessageSerializator::deserializeMeterageMessage(const std::string& message)
{
    std::vector<std::string> data = MessageSerializator::splitMessageString(message);
    return MeterageMessage(std::stoull(data[1]), (char)std::stoi(data[2]));
}



std::vector<std::string> MessageSerializator::splitMessageString(const std::string& message)
{
    std::stringstream stream;
    std::vector<std::string> data;
    for (char sim : message)
    {
        if (sim == ';')
        {
            data.emplace_back(stream.str());
            stream.str(std::string());
            continue;
        }
        stream << sim;
    }
    return data;
}

Message::MessageType MessageSerializator::identifySerializedMessageType(const std::string& message)
{
    std::vector<std::string> data = MessageSerializator::splitMessageString(message);
    if (data[0] == "Error")
    {
        return Message::MessageType::Error;
    }

    else if (data[0] == "Command")
    {
        return Message::MessageType::Command;
    }

    else
    {
        return Message::MessageType::Meterage;
    }
}
