#include <iostream>
#include <string>
#include <cstdint>
#include "serialiZer/serializer.h"
#include "../messages.h"

MessageBase DeSerializer::ToMessage(const std::string& messageStr) {
    std::istringstream stringy(messageStr); //  turn our \r separated string to stream
    std::string stage; // presumably got msgType
    stringy >> stage;
    MessageBase messageStruct{MsgType::Meterage, {0,0}, ErrType::NoErr, 0}; 
    MsgType type = static_cast<MsgType>(std::stoi(stage));
    messageStruct.MessageType = type;
    switch (type)
    {
    case MsgType::Meterage:

        stringy >> stage;
        messageStruct.data.timeStamp(std::stol(stage));
        stringy >> stage;
        messageStruct.data.timeStamp(std::stoi(stage));
        break;
    case MsgType::Command:
        MessageBase messageStruct{MsgType::Command, {0,0}, ErrType::NoErr, 0}; 
        stringy >> stage;
        messageStruct.correction(std::stol(stage));
        break;
     case MsgType::Error:
        MessageBase messageStruct{MsgType::Error, {0,0}, ErrType::NoErr, 0}; 
        stringy >> stage;
        messageStruct.data.timeStamp(static_cast<ErrType>(std::stoi(stage)));
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
        /* code */
        // MessageMetric& meterage dynamic_cast<MessageMetric&>(message);
        stringy << static_cast<int>(message.MessageType) << '\r' << message.data.timeStamp << '\r' << message.data.value << '\r';
        break;
    case MsgType::Command:
        /* code */
        // MessageCommand& command dynamic_cast<MessageCommand&>(message);
        stringy << static_cast<int8_t>(message.MessageType) << '\r' << message.correction << '\r';
        break;
    case MsgType::Error:
        /* code */
        // MessageError& error dynamic_cast<MessageError&>(message);
        stringy << static_cast<int8_t>(message.MessageType) << '\r' << static_cast<int8_t>(message.error);
        break;
    
    default:
        break;
    };
    return stringy.str()
}