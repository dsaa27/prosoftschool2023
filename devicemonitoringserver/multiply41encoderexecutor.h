#ifndef MULTIPLY41ENCODEREXECUTOR_H
#define MULTIPLY41ENCODEREXECUTOR_H

#include "baseencoderexecutor.h"

class Multiply41EncoderExecutor : public BaseEncoderExecutor
{
public:
    std::string encode(const std::string& message) override;
    std::string decode(const std::string& message) override;
    std::string name() const override { return "Multiply41"; }
};

#endif // MULTIPLY41ENCODEREXECUTOR_H