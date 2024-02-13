#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <iostream>

class AbstractMessage;

class Serializer
{
public:
    AbstractMessage* deserialize(const std::string& str_msg) const;
    std::string serialize(const AbstractMessage* msg);
};

#endif /* SERIALIZER_H */