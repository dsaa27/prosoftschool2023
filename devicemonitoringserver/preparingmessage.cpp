#include "preparingmessage.h"
#include "messageencoder.h"
#include "messageserializator.h"

std::string preparingmessages::packMessage(const AbstractMessage& message)
{
	return MessageEncoder::instance().encode(MessageSerializator::serialize(message));
}

pAbstractMessage preparingmessages::depackMessage(const std::string& message)
{
	return MessageSerializator::deserialize(MessageEncoder::instance().decode(message));
}
