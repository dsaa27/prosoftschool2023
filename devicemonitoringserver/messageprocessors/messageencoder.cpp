#include "messageencoder.h"

MessageEncoder::MessageEncoder()
{
    registerAlgorithm(new ROT3);
    registerAlgorithm(new Mirror);
    registerAlgorithm(new Multiply41);
}

MessageEncoder::MessageEncoder(const MessageEncoder& other)
{
    for (auto alg : other.m_algorithmLibrary)
    {
        registerAlgorithm(alg.second->clone());
    }
}

MessageEncoder::~MessageEncoder()
{
    for (auto& alg : m_algorithmLibrary)
    {
        delete alg.second;        
        alg.second = nullptr;
    }
}

namespace
{
    std::vector<uint8_t> decimalDisassembleNumber(uint64_t sim)
{
    std::vector<uint8_t> buff;
    while (sim != 0)
    {
        buff.emplace_back(sim % 10);
        sim /= 10;
    }
    return buff;
}

uint64_t decimalAssembleNumber(std::vector<uint8_t>& buff)
{
    uint64_t number = 0;
    for (char tenPow = buff.size() - 1; tenPow >= 0; tenPow--)
    {
        number += (buff[tenPow] * pow(10, tenPow));
    }
    return number;
}

uint64_t count_first_zero(const std::vector<uint8_t>& buff)
{
    uint64_t count = 0;
    for (auto el : buff)
    {
        if (el) break;
        ++count;
    }
    return count;
}

void mirrorByteBuffer(std::vector<uint8_t>& buff)
{
    std::reverse(buff.begin(), buff.end());
}
}

std::string MessageEncoder::encode(const std::string& str, BaseEncoderExecutor* alg) const
{
    return alg->encode(str);
}

std::string MessageEncoder::decode(const std::string& str, BaseEncoderExecutor* alg) const
{
    return alg->decode(str);
}

BaseEncoderExecutor* MessageEncoder::chooseAlgorithm(const std::string& name) const
{
    auto algIt = m_algorithmLibrary.find(name);
    return algIt==m_algorithmLibrary.end() ? nullptr : (*algIt).second;
}

void MessageEncoder::registerAlgorithm(BaseEncoderExecutor* alg)
{
    m_algorithmLibrary.emplace(alg->name(), alg);
}

MessageEncoder::ROT3::ROT3() :
    BaseEncoderExecutor("ROT3") {};

std::string MessageEncoder::ROT3::encode(const std::string& str) const
{
    std::string answer(str);
    for (auto& sim : answer)
    {
        sim += 3;
    }
    return answer;
}

std::string MessageEncoder::ROT3::decode(const std::string& str) const
{
    std::string answer(str);
    for (auto& sim : answer)
    {
        sim -= 3;
    }
    return answer;
}

MessageEncoder::ROT3* MessageEncoder::ROT3::clone() const
{
    return new ROT3();
}

MessageEncoder::Mirror::Mirror() :
    BaseEncoderExecutor("Mirror") {};

std::string MessageEncoder::Mirror::encode(const std::string& str) const
{
    std::stringstream answer;
    for (uint8_t sim : str)
    {
        auto byteBuffer = decimalDisassembleNumber(sim);
        answer << (char)count_first_zero(byteBuffer);
        mirrorByteBuffer(byteBuffer);
        uint16_t newPart = decimalAssembleNumber(byteBuffer);
        answer << (char)((newPart & 0xFF00) >> 8);
        answer << (char)(newPart & 0x00FF);
    }
    return answer.str();
}

std::string MessageEncoder::Mirror::decode(const std::string& str) const
{
    std::stringstream answer;
    char simNumber = 0;
    uint8_t tenPow;
    uint16_t number = 0;
    for (uint8_t sim : str)
    {
        switch (simNumber)
        {
        case 0:
            tenPow = sim;
            break;
        case 1:
            number += sim << 8;
            break;
        case 2:
            number += sim;
            auto byteBuffer = decimalDisassembleNumber(number);
            mirrorByteBuffer(byteBuffer);
            answer << (char)(decimalAssembleNumber(byteBuffer)*std::pow(10, tenPow));
            number = 0;
            break;
        }
        simNumber = (simNumber + 1) % 3;
    }
    return answer.str();
}

MessageEncoder::Mirror* MessageEncoder::Mirror::clone() const
{
    return new Mirror();
}

MessageEncoder::Multiply41::Multiply41() :
    BaseEncoderExecutor("Multiply41") {};

std::string MessageEncoder::Multiply41::encode(const std::string& str) const
{
    std::stringstream answer;
    for (uint8_t sim : str)
    {
        uint64_t newPart = decimalAssembleNumber(decimalDisassembleNumber((uint64_t)sim * 41));
        answer << (char)((newPart & 0xFF00) >> 8);
        answer << (char)(newPart & 0x00FF);
    }
    return answer.str();
}

std::string MessageEncoder::Multiply41::decode(const std::string& str) const
{
    std::stringstream answer;
    uint64_t number = 0;
    bool isEvenSim = false;
    for (uint8_t sim : str)
    {
        number += isEvenSim ? sim : sim << 8;
        if (isEvenSim)
        {
            answer << (char)decimalAssembleNumber(decimalDisassembleNumber(number/41));
            number = 0;
        }
        isEvenSim = !isEvenSim;
    }
    return answer.str();
}

MessageEncoder::Multiply41* MessageEncoder::Multiply41::clone() const
{
    return new Multiply41();
}
