#ifndef ABSTRACTBASEENCODEREXECUTOR_H
#define ABSTRACTBASEENCODEREXECUTOR_H
#include <string>
#include <memory>
class BaseEncoderExecutor
{
public:
	virtual std::string encode(const std::string&) const = 0;
	virtual std::string decode(const std::string&) const = 0;
	virtual std::string getName() const = 0;
	BaseEncoderExecutor(const std::string& name) : name(name) {};

protected:
	std::string name;
};

typedef std::shared_ptr<BaseEncoderExecutor> pBaseEncoderExecutor;

#endif // ABSTRACTBASEENCODEREXECUTOR_H
