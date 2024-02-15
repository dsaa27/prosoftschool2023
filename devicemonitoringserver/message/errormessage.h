#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H

#include "abstractmessage.h"

class ErrorMessage final : public AbstractMessage
{
public:

	enum class ErrorType
	{
		NoSchedule,
		NoTimestamp,
		Obsolete
	};

	ErrorMessage(ErrorType errorType) :
		AbstractMessage(AbstractMessage::MessageType::Error),
		m_errorType(errorType)
	{}

	std::string messageToString() const override;
    ErrorType getErrorType() const;

private:
	const ErrorType m_errorType;
};

#endif /* ERRORMESSAGE_H */