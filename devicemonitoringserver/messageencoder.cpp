#include "messageencoder.h"
#include "baseencoderexecutor.h"
#include "mirrorencoderexecutor.h"
#include "multiply41encoderexecutor.h"
#include "rot3encoderexecutor.h"

MessageEncoder::MessageEncoder()
{
    addExecutor(new Rot3EncoderExecutor());
    addExecutor(new MirrorEncoderExecutor());
    addExecutor(new Multiply41EncoderExecutor());
}

MessageEncoder::~MessageEncoder()
{
    for (auto executor : m_executors)
    {
        delete executor;
    }
}

std::string MessageEncoder::encode(const std::string& message)
{
    if (!m_currentExecutor)
        return std::string();
    return m_currentExecutor->encode(message);
}

std::string MessageEncoder::decode(const std::string& message)
{
    if (!m_currentExecutor)
        return std::string();
    return m_currentExecutor->decode(message);
}

bool MessageEncoder::selectExecutor(const std::string& name)
{
    for (auto executor : m_executors)
    {
        if (executor->name() == name)
        {
            m_currentExecutor = executor;
            return true;
        }
    }
    return false;
}

bool MessageEncoder::addExecutor(BaseEncoderExecutor* executor)
{
    if (!executor)
        return false;
    for (auto& e : m_executors)
    {
        if (e->name() == executor->name())
        {
            if (m_currentExecutor == e)
                m_currentExecutor = executor;
            delete e;
            e = executor;
            return true;
        }
    }
    m_executors.push_back(executor);
    return true;
}
