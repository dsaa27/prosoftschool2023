#ifndef ENCODER_H
#define ENCODER_H

#include "../algorithms/baseencoderexecutor.h"
#include "../algorithms/rot3.h"

#include <string>
#include <map>

class Encoder
{
public:
	const std::string decode(const std::string& message);
	const std::string encode(const std::string& message);

	bool algorithmSettedUp() const;
	bool algorithmExist(std::string str_alg) const;
	bool algorithmSet(std::string str_alg);
	bool algorithmRegister(BaseEncoderExecutor* alg);

	Encoder()
	{
		algorithmRegister(new Rot3Crypt());

		algorithmSet(CryptAlgDefault());
	}

	std::string CryptAlgDefault()
	{
         return "ROT3";
	}

private:
	std::map<std::string, BaseEncoderExecutor*> m_algorithmMap;
	BaseEncoderExecutor* m_currentAlgorithm = nullptr;
};

#endif /* ENCODER_H */
