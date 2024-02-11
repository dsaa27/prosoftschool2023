#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <sstream>
#include <memory>
struct AbstractMessage
{
	virtual std::string Serialize() const = 0;
	virtual void Deserialize(std::istringstream&) = 0;
};

typedef std::shared_ptr<AbstractMessage> pAbstractMessage;

#endif // MESSAGE_H

