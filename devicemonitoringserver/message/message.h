#pragma once
#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <sstream>
class Message
{
public:
    enum class MessageType
    {
        Meterage,
        Command,
        Error
    };

    MessageType getMessageType() const { return m_type; };
    bool operator==(const Message& other) { return m_type == other.m_type; }
    bool operator!=(const Message& other) { return m_type != other.m_type; }
    virtual std::string messageToString() const = 0;

protected:
    MessageType m_type = MessageType::Meterage;
};

#endif
