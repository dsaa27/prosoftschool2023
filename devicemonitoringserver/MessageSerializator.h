#ifndef MESSAGESERIALIZATOR_H
#define MESSAGESERIALIZATOR_H
#include "message/meterage.h"
#include "message/error.h"
#include "message/command.h"
#include "message/abstractmessage.h"
#include <string>

class MessageSerializator
{
public:
	static std::string Serialize(const AbstractMessage& data);
	static pAbstractMessage Deserialize(const std::string& data);
};

#endif // MESSAGESERIALIZATOR_H
