#include "multiply41.h"

#include <limits>

constexpr unsigned int MAX_CHAR = std::numeric_limits<char>() + 1;

std::string Multiply41Crypt::encode(const std::string& message) const
{
    std::string encodeMessage(message);
    for (auto& c : encodeMessage)
    {
        uint16_t c_temp = static_cast<uint16_t>(c);
        c_temp *= 41;
        c_temp %= MAX_CHAR;
        c = static_cast<char>(c_temp);
    }
    return encodeMessage;
}

std::string Multiply41Crypt::decode(const std::string& message) const
{
    std::string decodeMessage(message);
    for (auto& c : decodeMessage)
    {
        uint16_t c_temp = static_cast<uint16_t>(c);
        c_temp /= 41;
        c_temp = (MAX_CHAR + c_temp) % MAX_CHAR;
        c = static_cast<char>(c_temp);
    }
    return decodeMessage;
}