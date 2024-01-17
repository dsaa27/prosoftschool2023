#ifndef MIRRORENCODEREXECUTOR_H
#define MIRRORENCODEREXECUTOR_H

#include "baseencoderexecutor.h"

class MirrorEncoderExecutor : public BaseEncoderExecutor
{
public:
    std::string encode(const std::string& message) override;
    std::string decode(const std::string& message) override;
    std::string name() const override { return "Mirror"; }
};

#endif // MIRRORENCODEREXECUTOR_H