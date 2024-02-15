#ifndef MULTIPLY41_H
#define MULTIPLY41_H

#include "baseencoderexecutor.h"
#include <string>

class Multiply41Crypt final : public BaseEncoderExecutor
{
public:
    Multiply41CryptCrypt() :
        BaseEncoderExecutor("MULTIPLY41")
    {}
    std::string encode(const std::string& message) const override;
    std::string decode(const std::string& message) const override;
};

#endif /* MULTIPLY41_H */
