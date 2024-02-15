#ifndef ROT3_H
#define ROT3_H

#include "baseencoderexecutor.h"
#include <string>

class Rot3Crypt final : public BaseEncoderExecutor
{
public:
	Rot3Crypt() :
		BaseEncoderExecutor("ROT3")
	{}
	std::string encode(const std::string& message) const override;
	std::string decode(const std::string& message) const override;
};

#endif /* ROT3_H */
