#include "meteragemessage.h"

std::string MeterageMessage::messageToString() const
{
    std::stringstream stream;
    stream << "Meterage: " << static_cast<unsigned int>(m_meterage) << "; Timestamp: " << m_timeStamp;
    return stream.str();
}

uint64_t MeterageMessage::getTimestamp() const
{
    return m_timeStamp;
}

uint8_t MeterageMessage::getMeterage() const
{
    return m_meterage;
}
