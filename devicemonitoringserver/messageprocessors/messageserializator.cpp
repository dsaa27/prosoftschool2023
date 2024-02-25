#include "messageserializator.h"
#include <vector>


namespace MessageSerializator
{

    namespace
    {
    std::vector<std::string> splitMessageString(const std::string& message)
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
    }

    std::string serializeMessage(const MeterageMessage& message)
    {
        auto meterage = message.getMeterage();
        std::stringstream stream;
        stream << "Meterage;" << meterage.first << ';' << (int)meterage.second << ';';
        return stream.str();
    }

    std::string serializeMessage(const ErrorMessage& message)
    {
        std::stringstream stream;
        stream << "Error;";
        switch (message.getErrorType())
        {
        case ErrorMessage::ErrorType::NoSchedule:
            stream << "NoSchedule;";
            break;

        case ErrorMessage::ErrorType::NoTimestamp:
            stream << "NoTimestamp;";
            break;

        case ErrorMessage::ErrorType::Obsolete:
            stream << "Obsolete;";
            break;
        }
        return stream.str();
    }

    std::string serializeMessage(const CommandMessage& message)
    {
        std::stringstream stream;
        stream << "Command;" << (int)message.getAdjustment() << ';';
        return stream.str();
    }

    ErrorMessage deserializeErrorMessage(const std::string& message)
    {
        std::vector<std::string> data = splitMessageString(message);
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

CommandMessage deserializeCommandMessage(const std::string& message)
{
    std::vector<std::string> data = splitMessageString(message);
    return CommandMessage((char)std::stoi(data[1]));
}

MeterageMessage deserializeMeterageMessage(const std::string& message)
{
    std::vector<std::string> data = splitMessageString(message);
    return MeterageMessage(std::stoull(data[1]), (char)std::stoi(data[2]));
}

Message::MessageType identifySerializedMessageType(const std::string& message)
{
    std::vector<std::string> data = splitMessageString(message);
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
}


