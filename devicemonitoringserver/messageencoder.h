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
	static MessageEncoder& instance();
	std::string encode(const std::string&) const;
	std::string decode(const std::string&) const;
	bool chooseAlgorithm(const std::string&);
	void registerAlgorithm(const pBaseEncoderExecutor&);

private:
	MessageEncoder()
	{
		registerAlgorithm(pBaseEncoderExecutor(new ROT3()));
		registerAlgorithm(pBaseEncoderExecutor(new multiply41()));
		m_Algorithms = m_EncryptionAlgorithms["ROT3"];
	}
	std::map<std::string, pBaseEncoderExecutor> m_EncryptionAlgorithms;
	pBaseEncoderExecutor m_Algorithms;
};


#endif // MESSAGEENCODER_H
