#include "messageserializer.h"
#include "message.h"
#include "messagecommand.h"
#include "messageerror.h"
#include "messagemeterage.h"

#include <sstream>

std::string MessageSerializer::serialize(const Message& message) const
{
    std::ostringstream os(std::ios_base::binary);
    do
    {
        const MessageError* messageError = dynamic_cast<const MessageError*>(&message);
        if (messageError)
        {
            os.put('e');
            messageError->serialize(os);
            break;
        }
        const MessageCommand* messageCommand = dynamic_cast<const MessageCommand*>(&message);
        if (messageCommand)
        {
            os.put('c');
            messageCommand->serialize(os);
            break;
        }
        const MessageMeterage* messageMeterage = dynamic_cast<const MessageMeterage*>(&message);
        if (messageMeterage)
        {
            os.put('m');
            messageMeterage->serialize(os);
            break;
        }
        return std::string();
    } while (false);
    return os.str();
}

bool MessageSerializer::deserialize(const std::string& string, std::function<void(const Message&)> callback) const
{
    std::istringstream is(string, std::ios_base::binary);
    char ch = is.get();
    if (is.fail())
        return false;

    switch (ch)
    {
    case 'e':
        if (auto message = MessageError::deserialize(is))
        {
            callback(*message);
            return true;
        }
        break;
    case 'c':
        if (auto message = MessageCommand::deserialize(is))
        {
            callback(*message);
            return true;
        }
        break;
    case 'm':
        if (auto message = MessageMeterage::deserialize(is))
        {
            callback(*message);
            return true;
        }
        break;
    }
    return false;
}
