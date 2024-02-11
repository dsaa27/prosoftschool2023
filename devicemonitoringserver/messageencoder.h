#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H
#include <vector>
#include <map>
#include "abstractbaseencoderexecutor.h"
#include "rot3.h"
#include "multiply41.h"


struct MessageEncoder
{
public:
	MessageEncoder()
	{
		RegisterAlgorithm(pBaseEncoderExecutor(new ROT3()));
		RegisterAlgorithm(pBaseEncoderExecutor(new multiply41()));
		m_Algorithms = m_EncryptionAlgorithms["ROT3"];
	}
	std::string Encode(const std::string&) const;
	std::string Decode(const std::string&) const;
	bool ChooseAlgorithm(const std::string&);
	void RegisterAlgorithm(const pBaseEncoderExecutor&);

private:
	std::map<std::string, pBaseEncoderExecutor> m_EncryptionAlgorithms;
	pBaseEncoderExecutor m_Algorithms;
};

static MessageEncoder messageEncode = MessageEncoder();


#endif // MESSAGEENCODER_H
