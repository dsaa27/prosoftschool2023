#ifndef PREPARINGMESSAGES_H
#define PREPARINGMESSAGES_H

#include "message/abstractmessage.h"

#include <string>

namespace preparingmessages
{
	std::string PackMessage(const AbstractMessage&);
	pAbstractMessage DepackMessage(const std::string&);
};
#endif // PREPARINGMESSAGES_H
