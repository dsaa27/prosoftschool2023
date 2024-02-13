#include "error.h"

std::string Error::Serialize() const
{
	std::string message = "error ";
	switch (m_errorType) {
		case ErrorType::NoSchedule:
			message += "NoSchedule";
			break;
		case ErrorType::NoTimestamp:
			message += "NoTimestamp";
			break;
		default:
			message += "Obsolete";
	}
	return message;
}

void Error::Deserialize(std::istringstream& is)
{
	std::string strErrorType;
	is >> strErrorType;
	if (strErrorType == "NoSchedule")
	{
		m_errorType = ErrorType::NoSchedule;
	}
	else if (strErrorType == "NoTimestamp")
	{
		m_errorType = ErrorType::NoTimestamp;
	}
	else
	{
		m_errorType = ErrorType::Obsolete;
	}
}

ErrorType Error::GetErrorType() const
{
	return m_errorType;
}



