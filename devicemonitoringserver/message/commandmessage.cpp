#include "commandmessage.h"

std::string CommandMessage::messageToString() const
{
    std::stringstream stream;
    stream << "Command: " << static_cast<unsigned int>(m_adjustment);
    return stream.str();
}
