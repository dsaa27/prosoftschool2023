#ifndef MIRROR_H
#define MIRROR_H

#include "baseencoderexecutor.h"
#include <string>

class MirrorCrypt final : public BaseEncoderExecutor
{
public:
    MirrorCrypt() :
        BaseEncoderExecutor("MIRROR")
    {}
    std::string encode(const std::string& message) const override;
    std::string decode(const std::string& message) const override;
};

#endif /* MIRROR_H */
