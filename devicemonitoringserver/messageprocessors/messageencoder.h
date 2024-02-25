#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H 
#include <map>
#include <string>
#include "baseencoderexecutor.h"
#include <sstream>
#include <stack>
#include <algorithm>
#include <cmath>
class MessageEncoder
{
public:
    MessageEncoder();
    MessageEncoder(const MessageEncoder& other);
    ~MessageEncoder();
    void registerAlgorithm(BaseEncoderExecutor*);
    BaseEncoderExecutor* chooseAlgorithm(const std::string&) const;
    std::string encode(const std::string&, BaseEncoderExecutor*) const;
    std::string decode(const std::string&, BaseEncoderExecutor*) const;

private:
    class ROT3 final  : public BaseEncoderExecutor
    {
    public:
        ROT3();
        std::string encode(const std::string&) const override;
        std::string decode(const std::string&) const override;
    };

    class Mirror final : public BaseEncoderExecutor
    {
    public:
        Mirror();
        std::string encode(const std::string&) const override;
        std::string decode(const std::string&) const override;
    };

    class Multiply41 final : public BaseEncoderExecutor
    {
    public:
        Multiply41();
        std::string encode(const std::string&) const override;
        std::string decode(const std::string&) const override;
    };
    std::map<std::string, BaseEncoderExecutor*> m_algorithmLibrary;
};
#endif
