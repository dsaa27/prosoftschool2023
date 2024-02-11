#ifndef ROT3_H
#define ROT3_H
#include "abstractbaseencoderexecutor.h"

struct ROT3: BaseEncoderExecutor
{
public:
	ROT3() : BaseEncoderExecutor("ROT3") {}
	std::string Encode(const std::string &) const override final;
	std::string Decode(const std::string &) const override final;
	std::string Name() const override final;
};

#endif // ROT3_H
