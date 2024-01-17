#ifndef ROT3ENCODEREXECUTOR_H
#define ROT3ENCODEREXECUTOR_H

#include "baseencoderexecutor.h"

class Rot3EncoderExecutor : public BaseEncoderExecutor
{
public:
    std::string encode(const std::string& message) override;
    std::string decode(const std::string& message) override;
    std::string name() const override { return "ROT3"; }
};

#endif // ROT3ENCODEREXECUTOR_H