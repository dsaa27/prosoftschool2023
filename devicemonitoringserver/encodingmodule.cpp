#include "encodingmodule.h"

EncodingModule::EncodingModule(const MessageEncoder& encoder, const std::string& algorithmName) :
    m_encoder(encoder)
{
    setEncoderAlgorithm(algorithmName);
}

void EncodingModule::setEncoderAlgorithm(const std::string algorithmName)
{
    BaseEncoderExecutor* newAlgorithm = m_encoder.chooseAlgorithm(algorithmName);
    if (!newAlgorithm)
    {
        throw std::exception("Can't find algorithm. Did you register it? Default algorithms: 'ROT3', 'Mirror', 'Multiply41'");
    }
    m_encoderAlgorithm = newAlgorithm;
}

void EncodingModule::registerEncoderAlgorithm(BaseEncoderExecutor* algorithm)
{
    m_encoder.registerAlgorithm(algorithm);
}

std::string EncodingModule::encode(const std::string& message) const
{
    return m_encoder.encode(message, m_encoderAlgorithm);
}

std::string EncodingModule::decode(const std::string& message) const
{
    return m_encoder.decode(message, m_encoderAlgorithm);
}
