#ifndef MULTIPLY41_H
#define MULTIPLY41_H
#include "abstractbaseencoderexecutor.h"

class multiply41 : public BaseEncoderExecutor
{
public:
	multiply41() : BaseEncoderExecutor("Multiply41") {}
	std::string Encode(const std::string &) const override final;
	std::string Decode(const std::string &) const override final;
	std::string Name() const override final;
};

#endif // MULTIPLY41_H
