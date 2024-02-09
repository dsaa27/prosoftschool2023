#include "errormessage.h"

ErrorMessage::ErrorMessage(ErrorType error) :
    m_error(error)
{
    m_type = MessageType::Error;
}

std::string ErrorMessage::messageToString() const
{
    std::stringstream stream;
    stream << "Error;";
    switch (m_error)
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

ErrorMessage::ErrorType ErrorMessage::getErrorType() const
{
    return m_error;
}

std::ostream& operator<<(std::ostream& out, const ErrorMessage& other)
{
    out << other.messageToString();
    return out;
}

bool operator==(const ErrorMessage& error1, const ErrorMessage& error2)
{
    return error1.m_error == error2.m_error;
}

bool operator!=(const ErrorMessage& error1, const ErrorMessage& error2)
{
    return error1.m_error != error2.m_error;
}