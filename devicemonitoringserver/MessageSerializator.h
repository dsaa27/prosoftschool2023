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
	static std::string serialize(const AbstractMessage& data);
	static pAbstractMessage deserialize(const std::string& data);
};

#endif // MESSAGESERIALIZATOR_H
