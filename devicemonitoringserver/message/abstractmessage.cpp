#include "abstractmessage.h"

std::ostream& operator<<(std::ostream& out, const AbstractMessage& msg)
{
	out << msg.messageToString();
	return out;
}