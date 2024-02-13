#include "serializer.h"

#include "../message/abstractmessage.h"
#include "../message/commandmessage.h"
#include "../message/errormessage.h"
#include "../message/meteragemessage.h"

AbstractMessage* Serializer::deserialize(const std::string& str_msg) const
{
    std::istringstream stream(str_msg);

    AbstractMessage::MessageType typeMessage;

    {
        unsigned int typeTemp;
        stream >> typeTemp;
        typeMessage = static_cast<AbstractMessage::MessageType>(typeTemp);
    }

    AbstractMessage* msgTemp;

    switch (typeMessage)
    {
    case AbstractMessage::MessageType::Meterage:
    {
        uint64_t timeStamp = 0;
        uint16_t meterage = 0;
        stream >> meterage;
        stream >> timeStamp;
        msgTemp = dynamic_cast<MeterageMessage*>(new MeterageMessage(timeStamp, static_cast<uint8_t>(meterage)));
    }
    break;
    case AbstractMessage::MessageType::Error:
    {
        ErrorMessage::ErrorType errorType;
        {
            unsigned int typeTemp;
            stream >> typeTemp;
            errorType = static_cast<ErrorMessage::ErrorType>(typeTemp);
        }
        msgTemp = dynamic_cast<ErrorMessage*>(new ErrorMessage(errorType));
    }
    break;
    case AbstractMessage::MessageType::Command:
    {
        uint16_t adjustmentTemp;
        stream >> adjustmentTemp;
        uint8_t adjustment = static_cast<uint8_t>(adjustmentTemp);
        msgTemp = dynamic_cast<CommandMessage*>(new CommandMessage(adjustment));
    }
    break;
    }

    return msgTemp;
}

std::string Serializer::serialize(const AbstractMessage* message)
{
    std::ostringstream stream;
    AbstractMessage::MessageType typeMessage = message->getMessageType();

    stream << static_cast<unsigned int>(typeMessage) << ' ';

    switch (typeMessage)
    {
    case AbstractMessage::MessageType::Meterage:
    {
        const MeterageMessage* msgTemp = dynamic_cast<const MeterageMessage*>(message);
        stream << static_cast<unsigned int>(msgTemp->getMeterage()) << ' ';
        stream << msgTemp->getTimeStamp();
    }
    break;

    case AbstractMessage::MessageType::Command:
    {
        const CommandMessage* msgTemp = dynamic_cast<const CommandMessage*>(message);
        stream << static_cast<unsigned int>(msgTemp->getAdjustment());
    }
    break;

    case AbstractMessage::MessageType::Error:
    {
        const ErrorMessage* msgTemp = dynamic_cast<const ErrorMessage*>(message);
        stream << static_cast<unsigned int>(msgTemp->getErrorType());
    }
    break;
    }

    return stream.str();
}
