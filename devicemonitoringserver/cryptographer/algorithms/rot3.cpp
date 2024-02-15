#include "rot3.h"

std::string Rot3Crypt::encode(const std::string& message) const
{
    std::string encodeMessage(message);
    for (auto& c : encodeMessage)
    {
        c += 3;
    }
    return encodeMessage;
}

std::string Rot3Crypt::decode(const std::string& message) const
{
    std::string decodeMessage(message);
    for (auto& c : decodeMessage)
    {
        c -= 3;
    }
    return decodeMessage;
}
