#ifndef ERRORMESSAGE_H
#define ERRORMESSAGE_H
#include "message.h"

class ErrorMessage : public Message
{
public:
    enum class ErrorType
    {
        NoSchedule,
        NoTimestamp,
        Obsolete
    };

    ErrorMessage(ErrorType error);
    ~ErrorMessage() override = default;
    std::string messageToString() const override;
    ErrorType getErrorType() const;
    friend bool operator==(const ErrorMessage& error1, const ErrorMessage& error2);
    friend bool operator!=(const ErrorMessage& error1, const ErrorMessage& error2);
    friend std::ostream& operator<<(std::ostream& out, const ErrorMessage& other);

private:
    ErrorType m_error;
};


#endif
