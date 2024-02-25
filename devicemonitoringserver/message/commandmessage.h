#ifndef COMMANDMESSAGE_H
#define COMMANDMESSAGE_H
#include "message.h"
class CommandMessage final : public Message
{
public:
    CommandMessage(char adjustment);
    ~CommandMessage() override = default;
    std::string messageToString() const override;
    friend std::ostream& operator<<(std::ostream& out, const CommandMessage& other);
    friend bool operator==(const CommandMessage& command1, const CommandMessage& command2);
    friend bool operator!=(const CommandMessage& command1, const CommandMessage& command2);
    char getAdjustment() const;

private:
    char m_adjustment;
};
#endif
