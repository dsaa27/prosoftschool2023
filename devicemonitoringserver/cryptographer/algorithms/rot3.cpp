#include "rot3.h"

// if encoded symb == 0, so make it -1, like a specsymb;

constexpr unsigned int MAX_CHAR = std::numeric_limits<char>::max() + 1;
constexpr unsigned int MLT = 3;

std::string Rot3Crypt::encode(const std::string& message) const
{
    std::string encodeMessage(message);
    for (auto& c : encodeMessage)
    {
        c += MLT;
        if (c < 0) 
            c += MAX_CHAR;
        if (c == 0)
            c = -1;
    }
    return encodeMessage;
}

std::string Rot3Crypt::decode(const std::string& message) const
{
    std::string decodeMessage(message);
    for (auto& c : decodeMessage)
    {
        if (c == -1)
            c = static_cast<char>(MAX_CHAR - MLT);
        else
        {
            c -= MLT;
            if (c < 0)
                c += MAX_CHAR;
        }
    }
    return decodeMessage;
}
