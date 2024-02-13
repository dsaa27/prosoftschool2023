#ifndef COMMANDMESSAGE_H
#define COMMANDMESSAGE_H

#include "abstractmessage.h"

class CommandMessage final : public AbstractMessage
{
public:
	CommandMessage(const uint8_t adjustment) :
		AbstractMessage(AbstractMessage::MessageType::Command),
		m_adjustment(adjustment)
	{}

	std::string messageToString() const override;

	const uint8_t getAdjustment() const
	{
        return m_adjustment;
	}

private:
	const uint8_t m_adjustment;
};

#endif /* COMMANDMESSAGE_H */