#ifndef DUMMYENCODEREXECUTOR_H
#define DUMMYENCODEREXECUTOR_H

#include "baseencoderexecutor.h"

class DummyEncoderExecutor : public BaseEncoderExecutor
{
public:
    std::string encode(const std::string& message) override { return message; }
    std::string decode(const std::string& message) override { return message; }
    std::string name() override { return "Dummy"; }
};

#endif // DUMMYENCODEREXECUTOR_H