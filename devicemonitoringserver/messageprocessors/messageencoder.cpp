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
        BaseEncoderExecutor* alg_copy = (BaseEncoderExecutor*)malloc(sizeof(BaseEncoderExecutor));
        if (!alg_copy)
        {
            throw std::exception("can't copy encoder");
        }
        memcpy_s(alg_copy, sizeof(BaseEncoderExecutor), alg.second, sizeof(BaseEncoderExecutor));
        registerAlgorithm(alg_copy);
    }
}

MessageEncoder::~MessageEncoder()
{
    for (auto& alg : m_algorithmLibrary)
    {
        free(alg.second);        
        alg.second = nullptr;
    }
}

std::stack<uint8_t> decimalDisassembleNumber(uint64_t sim)
{
    std::stack<uint8_t> buff;
    while (sim != 0)
    {
        buff.push(sim % 10);
        sim /= 10;
    }
    return buff;
}

uint64_t decimalAssembleNumber(std::stack<uint8_t> buff)
{
    uint64_t number = 0;
    for (char tenPow = buff.size() - 1; tenPow >= 0; tenPow--)
    {
        number += (buff.top() * pow(10, tenPow));
        buff.pop();
    }
    return number;
}

uint64_t count_first_zero(std::stack<uint8_t> buff)
{
    auto container = buff._Get_container();
    uint64_t count = 0;
    for (auto el : container)
    {
        if (el) break;
        ++count;
    }
    return count;
}

void mirrorByteBuffer(std::stack<uint8_t>& buff)
{
    auto container = buff._Get_container();
    std::reverse(container.begin(), container.end());
    buff = std::stack<uint8_t>(container);
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
    m_algorithmLibrary.emplace(std::pair<std::string, BaseEncoderExecutor*>(alg->name(), alg));
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
