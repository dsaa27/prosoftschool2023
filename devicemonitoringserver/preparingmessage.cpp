#include "preparingmessage.h"
#include "messageencoder.h"
#include "messageserializator.h"

std::string preparingmessages::PackMessage(const AbstractMessage& message)
{
	return MessageEncoder::Instance().Encode(MessageSerializator::Serialize(message));
}

pAbstractMessage preparingmessages::DepackMessage(const std::string& message)
{
	return MessageSerializator::Deserialize(MessageEncoder::Instance().Decode(message));
}
