#ifndef MESSAGESERIALIZATOR_H
#define MESSAGESERIALIZATOR_H

#include "messages.h"
#include <iostream>
#include <string>
#include <sstream>
#include <utility>

namespace {
    std::ostringstream& operator<<(std::ostringstream& buf, const messageType type) {
        buf << static_cast<int>(type);
        return buf;
    } 

    std::ostringstream& operator<<(std::ostringstream& buf, const errorType error) {
        buf << static_cast<int>(error);
        return buf;
    }

   
}


class messageSerializator {
public:

    // overload for meterageMessage
    static std::string serialize(const meterageMessage* msg) {
        std::ostringstream buf;
        buf << msg->_type << ' ';
        buf << static_cast<int>(msg->_timeStamp) << ' ';
        buf << static_cast<int>(msg->_meterage);
        delete msg;
        return buf.str();
    }

    // overload for commandMessage
    static std::string serialize(const commandMessage* msg) {
        std::ostringstream buf;
        buf << msg->_type << ' ';
        buf << static_cast<int>(msg->_correctCommand);
        delete msg;
        return buf.str();
    }

    // overload for errorMessage
    static std::string serialize(const errorMessage* msg) {
        std::ostringstream buf;
        buf << msg->_type << ' ';
        buf << msg->_error;
        delete msg;
        return buf.str();
    }

    static std::pair<messageType, void*> deserialize(const std::string& str) {

        std::istringstream stream(str);
        int num; messageType type;
        stream >> num;
        type = static_cast<messageType>(num);

        std::pair<messageType, void*> p;
        p.first = type;

        switch(type){
            case messageType::Meterage:
                {
                    int timeStamp, meterage;
                    stream >> timeStamp >> meterage;
                    meterageMessage* msg = new meterageMessage(
                                            static_cast<uint64_t>(timeStamp),
                                            static_cast<uint8_t>(meterage));
                    p.second = reinterpret_cast<void*>(msg);
                }
                break;

            case messageType::Command:
                {
                    int command;
                    stream >> command;
                    commandMessage* msg = new commandMessage(
                                            static_cast<int8_t>(command));
                    p.second = reinterpret_cast<void*>(msg);
                }
                break;

            case messageType::Error:
                {
                    int error;
                    stream >> error;
                    errorMessage* msg = new errorMessage(
                                            static_cast<errorType>(error));
                    p.second = reinterpret_cast<void*>(msg);
                }
                break;

        }

        return p;
    }
};

#endif