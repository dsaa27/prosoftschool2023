#ifndef MULTIPLY41ENCODEREXECUTOR_H
#define MULTIPLY41ENCODEREXECUTOR_H

#include "baseencoderexecutor.h"

class Multiply41EncoderExecutor final : public BaseEncoderExecutor
{
    std::string encode(const std::string& message) const override;
    std::string decode(const std::string& message) const override;
    std::string name() const override { return "Multiply41"; }
};

#endif // MULTIPLY41ENCODEREXECUTOR_H