#include "messageserializator.h"

std::string MessageSerializator::serialize(const AbstractMessage& data)
{
	return data.serialize();
}

pAbstractMessage MessageSerializator::deserialize(const std::string& data)
{
	std::string messageType;
	pAbstractMessage msg;
	std::istringstream is(data);
	is >> messageType;
	if (messageType == "meterage")
	{
		msg = pMeterage(new Meterage());
	}
	else if (messageType == "command")
	{
		msg = pCommand(new Command());
	}
	else
	{
		msg = pError(new Error());
	}
	msg->deserialize(is);
	return msg;
}
