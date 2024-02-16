#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H

#include "encoderexecutor.h"
#include <vector>

class messageEncoder {
public:

    messageEncoder() {
        coders.push_back(new ROT3);
        coders.push_back(new Mirror);
        coders.push_back(new Multiply41);
    }

    ~messageEncoder() {
        for(baseEncoderExecutor* ptr : coders) {
            delete ptr;
        }
    }

    bool addCoder(baseEncoderExecutor* newCoder) {
        if (newCoder == nullptr)
            return false;

        coders.push_back(newCoder);
        return true;
    }

    bool chooseCoder(const std::string& str) {
        for(baseEncoderExecutor* ptr : coders) {
            if (ptr->name() == str) {
                currentCoder = ptr;
                return true;
            }
        }
        return false;
    }

    std::string encrypt(const std::string& str) {
        if (currentCoder != nullptr)
            return currentCoder->encode(str);
        return "";
    }

    std::string decrypt(const std::string& str) {
        if (currentCoder != nullptr)
            return currentCoder->decode(str);
        return "";
    } 

private:

    std::vector<baseEncoderExecutor*> coders = {};
    baseEncoderExecutor* currentCoder = nullptr;

};

#endif