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

	std::string serialize()const override final;
	void deserialize(std::istringstream&) override final;

	ErrorType getErrorType() const;

	bool operator ==(const Error&) const;
	bool operator !=(const Error&) const;
	friend std::ostream &operator << (std::ostream&, const Error&);

private:
	ErrorType m_errorType;
};

typedef std::shared_ptr<Error> pError;

#endif // ERROR_H
