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
		stream << "NoTimestamp";
		break;
	}
	return
}