#include <iostream>
#include <string>
#include <cstdint>
#include "serialiZer/serializer.h"
#include "../messages.h"

MessageBase * DeSerializer::ToMessage(const std::string& messageStr){

}

std::string DeSerializer::ToBytesArray(const MessageBase& message){
    std::ostringstream stringy;
    switch (message->MessageType)
    {
    case MsgType::Meterage:
        /* code */
        MessageMetric& meterage dynamic_cast<MessageMetric&>(message);
        stringy << static_cast<int>(meterage.MessageType) << meterage.data.timeStamp << meterage.data.value << endl;
        break;
    case MsgType::Command:
        /* code */
        MessageCommand& command dynamic_cast<MessageCommand&>(message);
        stringy << static_cast<int8_t>(command.MessageType) << command.correction << endl;
        break;
    case MsgType::Error:
        /* code */
        MessageError& error dynamic_cast<MessageError&>(message);
        stringy << static_cast<int8_t>(error.MessageType) << static_cast<int8_t>(error.error);
        break;
    
    default:
        break;
    };
    return stringy.str()
}