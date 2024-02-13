#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H
#include <vector>
#include <map>
#include "abstractbaseencoderexecutor.h"
#include "algorithm/rot3.h"
#include "algorithm/multiply41.h"


class MessageEncoder
{
public:
	static MessageEncoder& Instance();
	std::string Encode(const std::string&) const;
	std::string Decode(const std::string&) const;
	bool ChooseAlgorithm(const std::string&);
	void RegisterAlgorithm(const pBaseEncoderExecutor&);

private:
	MessageEncoder()
	{
		RegisterAlgorithm(pBaseEncoderExecutor(new ROT3()));
		RegisterAlgorithm(pBaseEncoderExecutor(new multiply41()));
		m_Algorithms = m_EncryptionAlgorithms["ROT3"];
	}
	std::map<std::string, pBaseEncoderExecutor> m_EncryptionAlgorithms;
	pBaseEncoderExecutor m_Algorithms;
};


#endif // MESSAGEENCODER_H
