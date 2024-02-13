#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <sstream>
#include <memory>
class AbstractMessage
{
public:
	virtual std::string serialize() const = 0;
	virtual void deserialize(std::istringstream&) = 0;
};

typedef std::shared_ptr<AbstractMessage> pAbstractMessage;

#endif // MESSAGE_H

