#include "rot3encoderexecutor.h"

#include <limits>

static constexpr int start = std::numeric_limits<char>::min();
static constexpr int end = std::numeric_limits<char>::max() + 1;

std::string Rot3EncoderExecutor::encode(const std::string& message) const
{
    std::string encoded;
    encoded.reserve(message.size());
    for (int c : message)
    {
        if (c >= start && c < end)
        {
            c += 3;
            if (c >= end)
                c -= end - start;
            encoded += c;
        }
    }
    return encoded;
}

std::string Rot3EncoderExecutor::decode(const std::string& message) const
{
    std::string decoded;
    decoded.reserve(message.size());
    for (int c : message)
    {
        if (c >= start && c < end)
        {
            c -= 3;
            if (c < start)
                c += end - start;
        }
        decoded += c;
    }
    return decoded;
}
