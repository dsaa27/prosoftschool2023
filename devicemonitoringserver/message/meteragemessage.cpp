#include "meteragemessage.h"

std::string MeterageMessage::messageToString() const
{
    std::stringstream stream;
    stream << "Meterage: " << m_meterage << "; Timestamp: " << m_timeStamp;
    return stream.str();
}