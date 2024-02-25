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
        if (data.at(1) == "NoSchedule")
            errorType = ErrorMessage::ErrorType::NoSchedule;

        else if (data.at(1) == "NoTimestamp")
            errorType = ErrorMessage::ErrorType::NoTimestamp;

        else if (data.at(1) == "Obsolete")
            errorType = ErrorMessage::ErrorType::Obsolete;

        else       
            throw std::exception("Wrong message format!");
        
        return ErrorMessage(errorType);
    }

CommandMessage deserializeCommandMessage(const std::string& message)
{
    std::vector<std::string> data = splitMessageString(message);
        return CommandMessage((char)std::stoi(data.at(1)));
}

MeterageMessage deserializeMeterageMessage(const std::string& message)
{
    std::vector<std::string> data = splitMessageString(message);
    return MeterageMessage(std::stoull(data.at(1)), (char)std::stoi(data.at(2)));
}

Message::MessageType identifySerializedMessageType(const std::string& message)
{
    std::vector<std::string> data = splitMessageString(message);
    if (data.at(0) == "Error")
        return Message::MessageType::Error;

    if (data.at(0) == "Command")
        return Message::MessageType::Command;

    if (data.at(0) == "Meterage")
        return Message::MessageType::Meterage;

    throw std::exception("Wrong message format!");

}
}


