#include "error.h"

std::string Error::serialize() const
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

void Error::deserialize(std::istringstream& is)
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

ErrorType Error::getErrorType() const
{
	return m_errorType;
}

bool Error::operator ==(const Error& error) const
{
	return this->getErrorType() == error.getErrorType();
}

bool Error::operator !=(const Error& error) const
{
	return !(this ->getErrorType() != error.getErrorType());
}

std::ostream &operator << (std::ostream& os, const Error& error)
{
	os << error.getErrorType();
	return os;
}



