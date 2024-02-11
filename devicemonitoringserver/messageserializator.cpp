#include "messageserializator.h"

std::string MessageSerializator::Serialize(const AbstractMessage& data)
{
	return data.Serialize();
}

pAbstractMessage MessageSerializator::Deserialize(const std::string& data)
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
	msg->Deserialize(is);
	return msg;
}
