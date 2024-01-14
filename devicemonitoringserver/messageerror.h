#ifndef MESSAGEERROR_H
#define MESSAGEERROR_H

#include "message.h"

/*!
 * \brief Класс сообщения об ошибке
 */
class MessageError final : public Message
{
public:
    /*!
    * \brief Перечисление типов ошибок
    */
    enum class ErrorType
    {
        NoSchedule,
        NoTimestamp,
        Obsolete
    };
    /*!
     * \brief Конструктор.
     * \param errorType - тип ошибки
     */
    MessageError(ErrorType errorType) :
        m_errorType(errorType) {}

    /*!
     * \brief Тип ошибки
     */
    ErrorType errorType() const { return m_errorType; }

    bool operator==(const Message& other) const override
    {
        const MessageError* o = dynamic_cast<const MessageError*>(&other);
        return o && errorType() == o->errorType();
    }

    std::ostream& print(std::ostream& os) const override;

private:
    const ErrorType m_errorType;
};

inline std::ostream& operator<<(std::ostream& os, MessageError::ErrorType t)
{
    os << "MessageError::ErrorType::";
    switch (t)
    {
    case MessageError::ErrorType::NoSchedule:
        os << "NoSchedule";
        break;
    case MessageError::ErrorType::NoTimestamp:
        os << "NoTimestamp";
        break;
    case MessageError::ErrorType::Obsolete:
        os << "Obsolete";
        break;
    default:
        os << "<unknown>";
    }
    return os;
}

inline std::ostream& MessageError::print(std::ostream& os) const
{
    return os << "MessageError (errorType=" << errorType() << ")";
}

#endif // MESSAGEERROR_H