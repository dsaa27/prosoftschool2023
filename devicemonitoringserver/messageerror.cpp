#include "messageerror.h"

#include <optional>

void MessageError::serialize(std::ostream& os) const
{
    switch (errorType())
    {
    case MessageError::ErrorType::NoSchedule:
        os.put('s');
        break;
    case MessageError::ErrorType::NoTimestamp:
        os.put('t');
        break;
    case MessageError::ErrorType::Obsolete:
        os.put('o');
        break;
    }
}

std::optional<MessageError> MessageError::deserialize(std::istream& is)
{
    char ch = is.get();
    if (is.fail())
        return {};
    switch (ch)
    {
    case 's':
        return MessageError(MessageError::ErrorType::NoSchedule);
    case 't':
        return MessageError(MessageError::ErrorType::NoTimestamp);
    case 'o':
        return MessageError(MessageError::ErrorType::Obsolete);
    }
    return {};
}
