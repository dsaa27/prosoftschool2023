#ifndef BASEENCODEREXECUTOR_H
#define BASEENCODEREXECUTOR_H

#include <string>

class BaseEncoderExecutor
{
public:
	BaseEncoderExecutor(std::string name) :
		m_algName(name)
	{}

	virtual ~BaseEncoderExecutor() = default;
	virtual std::string encode(const std::string& input) const = 0;
	virtual std::string decode(const std::string& input) const = 0;
	std::string name() const
	{
		return m_algName;
	}

protected:
	const std::string m_algName;
};

#endif /* BASEENCODEREXECUTOR_H */