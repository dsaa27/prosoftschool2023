#include "encoder.h"

const std::string Encoder::decode(const std::string& message)
{
	m_currentAlgorithm->decode(message);
}

const std::string Encoder::encode(const std::string& message)
{
	m_currentAlgorithm->encode(message);
}

bool Encoder::algorithmExist(std::string str_alg) const
{
	if (m_algorithmMap.count(str_alg) != 0)
		return true;
	return false;
}

bool Encoder::algorithmSet(std::string str_alg)
{
	if (algorithmExist(str_alg)) return false;
	m_currentAlgorithm = m_algorithmMap[str_alg];
	return true;
}

bool Encoder::algorithmAdd(BaseEncoderExecutor* alg)
{
	if (alg == nullptr) return false;
	m_algorithmMap[alg->name()] = alg;
	return true;
}

bool Encoder::algorithmSettedUp() const
{
	if (m_currentAlgorithm != nullptr)
		return true;
	return false;
}