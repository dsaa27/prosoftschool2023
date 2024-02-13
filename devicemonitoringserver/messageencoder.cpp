#include "messageencoder.h"


MessageEncoder& MessageEncoder::instance()
{
	static MessageEncoder messageEncoder;
	return messageEncoder;
}

std::string MessageEncoder::encode(const std::string& message) const
{
	return m_Algorithms->encode(message);
}

std::string MessageEncoder::decode(const std::string& encodedMessage) const
{
	return m_Algorithms->decode(encodedMessage);
}

bool MessageEncoder::chooseAlgorithm(const std::string& algorithm)
{
	if (!m_EncryptionAlgorithms.count(algorithm))
	{
		return false;
	}
	m_Algorithms = pBaseEncoderExecutor(m_EncryptionAlgorithms[algorithm]);
	return true;
}

void MessageEncoder::registerAlgorithm(const pBaseEncoderExecutor& newAlgorithm)
{
	if (!m_EncryptionAlgorithms.count(newAlgorithm->getName()))
	{
		m_EncryptionAlgorithms[newAlgorithm->getName()] = newAlgorithm;
	}
}
