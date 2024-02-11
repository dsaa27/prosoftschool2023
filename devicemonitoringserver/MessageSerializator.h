#ifndef MESSAGESERIALIZATOR_H
#define MESSAGESERIALIZATOR_H
#include "meterage.h"
#include "error.h"
#include "command.h"
#include <string>

class MessageSerializator
{
public:
	static std::string Serialize(const AbstractMessage& data);
	static pAbstractMessage Deserialize(const std::string& data);
};

#endif // MESSAGESERIALIZATOR_H
