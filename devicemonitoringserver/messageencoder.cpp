#include "messageencoder.h"


MessageEncoder& MessageEncoder::Instance()
{
	static MessageEncoder messageEncoder;
	return messageEncoder;
}

std::string MessageEncoder::Encode(const std::string& message) const
{
	return m_Algorithms->Encode(message);
}

std::string MessageEncoder::Decode(const std::string& encodedMessage) const
{
	return m_Algorithms->Decode(encodedMessage);
}

bool MessageEncoder::ChooseAlgorithm(const std::string& algorithm)
{
	if (!m_EncryptionAlgorithms.count(algorithm))
	{
		return false;
	}
	m_Algorithms = pBaseEncoderExecutor(m_EncryptionAlgorithms[algorithm]);
	return true;
}

void MessageEncoder::RegisterAlgorithm(const pBaseEncoderExecutor& newAlgorithm)
{
	if (!m_EncryptionAlgorithms.count(newAlgorithm->Name()))
	{
		m_EncryptionAlgorithms[newAlgorithm->Name()] = newAlgorithm;
	}
}
