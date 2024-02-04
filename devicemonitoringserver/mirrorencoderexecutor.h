#ifndef MIRRORENCODEREXECUTOR_H
#define MIRRORENCODEREXECUTOR_H

#include "baseencoderexecutor.h"

class MirrorEncoderExecutor final : public BaseEncoderExecutor
{
    std::string encode(const std::string& message) const override;
    std::string decode(const std::string& message) const override;
    std::string name() const override { return "Mirror"; }
};

#endif // MIRRORENCODEREXECUTOR_H