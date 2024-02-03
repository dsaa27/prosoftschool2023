#ifndef SERDESER_H
#define SERDESER_H

#include <string>
#include <iostream>
#include "../messages.h"

class DeSerializer {
public:
    MessageBase *ToMessage(const std::string& messageStr);
    std::string ToBytesArray(const MessageBase& message);
};

#endif