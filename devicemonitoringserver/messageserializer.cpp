#include "messageserializer.h"
#include "bigendian.h"
#include "message.h"
#include "messagecommand.h"
#include "messageerror.h"
#include "messagemeterage.h"

#include <sstream>

std::string MessageSerializer::serialize(const Message& message)
{
    std::ostringstream ostream(std::ios_base::binary);
    do
    {
        const MessageError* messageError = dynamic_cast<const MessageError*>(&message);
        if (messageError)
        {
            bool success = false;
            ostream.put('e');
            switch (messageError->errorType())
            {
            case MessageError::ErrorType::NoSchedule:
                ostream.put('s');
                success = true;
                break;
            case MessageError::ErrorType::NoTimestamp:
                ostream.put('t');
                success = true;
                break;
            case MessageError::ErrorType::Obsolete:
                ostream.put('o');
                success = true;
                break;
            }
            if (success)
                break;
        }
        const MessageCommand* messageCommand = dynamic_cast<const MessageCommand*>(&message);
        if (messageCommand)
        {
            ostream.put('c');
            toBigEndian(ostream, messageCommand->command());
            break;
        }
        const MessageMeterage* messageMeterage = dynamic_cast<const MessageMeterage*>(&message);
        if (messageMeterage)
        {
            ostream.put('m');
            toBigEndian(ostream, messageMeterage->timeStamp());
            toBigEndian(ostream, messageMeterage->meterage());
            break;
        }
        return std::string();
    } while (false);
    return ostream.str();
}

bool MessageSerializer::deserialize(const std::string& string, std::function<void(const Message&)> callback)
{
    std::istringstream istream(string, std::ios_base::binary);
    char ch = istream.get();
    if (istream.fail())
        return false;

    switch (ch)
    {
    case 'e':
        ch = istream.get();
        if (istream.fail())
            return false;
        switch (ch)
        {
        case 's':
            callback(MessageError(MessageError::ErrorType::NoSchedule));
            return true;
        case 't':
            callback(MessageError(MessageError::ErrorType::NoTimestamp));
            return true;
        case 'o':
            callback(MessageError(MessageError::ErrorType::Obsolete));
            return true;
        }
        break;
    case 'c':
        int command;
        command = fromBigEndian<int8_t>(istream);
        if (istream.fail())
            break;
        callback(MessageCommand(command));
        return true;
    case 'm':
        uint64_t timeStamp;
        uint8_t meterage;
        timeStamp = fromBigEndian<uint64_t>(istream);
        meterage = fromBigEndian<uint8_t>(istream);
        if (istream.fail())
            break;
        callback(MessageMeterage(timeStamp, meterage));
        return true;
    }
    return false;
}
