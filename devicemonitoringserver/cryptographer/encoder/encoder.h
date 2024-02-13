#ifndef ENCODER_H
#define ENCODER_H

#include "../algorithms/baseencoderexecutor.h"
#include "../algorithms/rot3.h"

#include <string>
#include <map>

class Encoder
{
	const std::string decode(const std::string& message);
	const std::string encode(const std::string& message);

	bool algorithmSettedUp() const;
	bool algorithmExist(std::string str_alg) const;
	bool algorithmSet(std::string str_alg);
	bool algorithmAdd(BaseEncoderExecutor* alg);

	Encoder()
	{
		algorithmAdd(new Rot3Crypt());
	}

private:
	std::map<std::string, BaseEncoderExecutor*> m_algorithmMap;
	BaseEncoderExecutor* m_currentAlgorithm = nullptr;
};

#endif /* ENCODER_H */
