#ifndef METERAGEMESSAGE_H
#define METERAGEMESSAGE_H

#include "abstractmessage.h"

class MeterageMessage final : public AbstractMessage
{
public:

	MeterageMessage(uint64_t timeStamp, uint8_t meterage) :
		AbstractMessage(AbstractMessage::MessageType::Meterage),
		m_timeStamp(timeStamp),
		m_meterage(meterage)
	{}

	std::string messageToString() const override;
    uint64_t getTimestamp() const;
    uint8_t getMeterage() const;

private:
	const uint64_t m_timeStamp = 0;
	const uint8_t m_meterage = 0;
};

#endif /* METERAGEMESSAGE_H */