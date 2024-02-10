#pragma once
#ifndef BASEENCODEREXECUTOR_H
#define BASEENCODEREXECUTOR_H
#include <string>
class BaseEncoderExecutor
{
public:
    BaseEncoderExecutor(std::string name) :
        m_name(name) {}
    virtual std::string encode(const std::string&) const = 0;
    virtual std::string decode(const std::string&) const = 0;
    std::string name() { return m_name; };
private:
    std::string m_name;
};
#endif
