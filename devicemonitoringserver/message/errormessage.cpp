#include "errormessage.h"

std::string ErrorMessage::messageToString() const
{
	std::stringstream stream;
	stream << "Error: ";
	switch (m_errorType)
	{
	case ErrorType::NoSchedule:
		stream << "NoSchedule";
		break;
	case ErrorType::NoTimestamp:
		stream << "NoTimestamp";
		break;
	case ErrorType::Obsolete:
		stream << "Obsolete";
		break;
	}

    return stream.str();
}

ErrorMessage::ErrorType ErrorMessage::getErrorType() const
{
    return m_errorType;
}
