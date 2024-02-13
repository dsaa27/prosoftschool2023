#ifndef PREPARINGMESSAGES_H
#define PREPARINGMESSAGES_H

#include "message/abstractmessage.h"

#include <string>

namespace preparingmessages
{
	std::string packMessage(const AbstractMessage&);
	pAbstractMessage depackMessage(const std::string&);
};
#endif // PREPARINGMESSAGES_H
