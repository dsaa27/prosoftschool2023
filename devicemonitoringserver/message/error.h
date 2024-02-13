#ifndef ERROR_H
#define ERROR_H
#include "abstractmessage.h"

enum ErrorType
{
	NoSchedule,
	NoTimestamp,
	Obsolete
};

class Error: public AbstractMessage
{
public:
	Error(const ErrorType& error = ErrorType::NoSchedule): m_errorType(error) {}

	std::string Serialize()const override final;
	void Deserialize(std::istringstream&) override final;

	ErrorType GetErrorType() const;

private:
	ErrorType m_errorType;
};

typedef std::shared_ptr<Error> pError;

#endif // ERROR_H
