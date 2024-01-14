#ifndef MESSAGECOMMAND_H
#define MESSAGECOMMAND_H

#include "message.h"

#include <cstdint>

/*!
 * \brief Класс сообщения с командой для корректировки физического параметра
 */
class MessageCommand final : public Message
{
public:
    /*!
     * \brief Конструктор.
     * \param command - величина для коррекции физического параметра
     */
    MessageCommand(int8_t command) :
        m_command(command) {}

    /*!
     * \brief Величина для коррекции физического параметра
     */
    int8_t command() const { return m_command; }

    bool operator==(const Message& other) const
    {
        const MessageCommand* o = dynamic_cast<const MessageCommand*>(&other);
        return o && command() == o->command();
    }

    std::ostream& print(std::ostream& os) const override
    {
        return os << "MessageCommand (command=" << command() << ")";
    }

private:
    const int8_t m_command;
};

#endif // MESSAGECOMMAND_H