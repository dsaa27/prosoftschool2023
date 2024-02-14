#include <iostream>
#include <sstream>
#include <string> 
#include <cstdint>
#include "serialiZer/serializer.h"
#include "../messages.h"

MessageBase DeSerializer::ToMessage(const std::string& messageStr) {
    std::istringstream stringy(messageStr); //  turn our \r separated string to stream
    std::string stage; // presumably got msgType
    stringy >> stage;
    MessageBase messageStruct{MsgType::Meterage, {0,0}, ErrType::NoErr, 0}; 
    MsgType type = static_cast<MsgType>(std::stoul(stage));
    messageStruct.MessageType = type;
    switch (type)
    {
    case MsgType::Meterage:
        stringy >> stage;
        messageStruct.data.timeStamp = (std::stoul(stage));
        stringy >> stage;
        messageStruct.data.value = (std::stoul(stage));
        break;
    case MsgType::Command:
        stringy >> stage;
        messageStruct.correction = (std::stol(stage));
        break;
    case MsgType::Error:
        stringy >> stage;
        messageStruct.error = (static_cast<ErrType>(std::stol(stage)));
        break;           
    default:
        break;
    }
    return messageStruct;

}

std::string DeSerializer::ToBytesArray(const MessageBase& message){
    std::ostringstream stringy;
    switch (message.MessageType)
    {
    case MsgType::Meterage:

        stringy << static_cast<unsigned int>(message.MessageType) << ' ' << message.data.timeStamp << ' ' << static_cast<unsigned int>(message.data.value) << std::endl;
        break;
    case MsgType::Command:

        stringy << static_cast<unsigned int>(message.MessageType) << ' ' << static_cast<unsigned int>(message.correction) << std::endl;
        break;
    case MsgType::Error:

        stringy << static_cast<unsigned int>(message.MessageType) << ' ' << static_cast<unsigned int>(message.error) << std::endl;
        break;
    
    default:
        stringy << std::endl;
        break;
    };
    std::string res = stringy.str();
    return res;
}