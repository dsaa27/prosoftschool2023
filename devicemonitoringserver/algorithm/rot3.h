#ifndef ROT3_H
#define ROT3_H
#include "abstractbaseencoderexecutor.h"

class ROT3: public BaseEncoderExecutor
{
public:
	ROT3() : BaseEncoderExecutor("ROT3") {}
	std::string encode(const std::string &) const override final;
	std::string decode(const std::string &) const override final;
	std::string getName() const override final;
};

#endif // ROT3_H
