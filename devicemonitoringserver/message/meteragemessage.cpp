#include "meteragemessage.h"

MeterageMessage::MeterageMessage(uint64_t timeStamp, char meterage) :
    Message(MessageType::Meterage)
{
    m_meterage = std::pair<uint64_t, char>(timeStamp, meterage);
}

std::string MeterageMessage::messageToString() const
{
    std::stringstream stream;
    stream << "Meterage;" << m_meterage.first << ';' << (int)m_meterage.second <<';';
    return stream.str();
}

std::pair<uint64_t, char> MeterageMessage::getMeterage() const
{
    return m_meterage;
}

std::ostream& operator<<(std::ostream& out, const MeterageMessage& other)
{
    out << other.messageToString();
    return out;
}

bool operator==(const MeterageMessage& meterage1, const MeterageMessage& meterage2)
{
    return meterage1.m_meterage == meterage2.m_meterage;
}

bool operator!=(const MeterageMessage& meterage1, const MeterageMessage& meterage2)
{
    return meterage1.m_meterage != meterage2.m_meterage;
}
