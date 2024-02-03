#include "mirrorencoderexecutor.h"
#include "bigendian.h"

#include <cassert>
#include <cstdint>
#include <sstream>

static int digits(uint16_t value)
{
    int digits = 0;
    while (value > 0)
    {
        value /= 10;
        ++digits;
    };
    return digits;
}

static uint16_t mirror(uint16_t value, int digits)
{
    uint16_t result = 0;
    for (int i = 0; i < digits; ++i)
    {
        result *= 10;
        result += value % 10;
        value /= 10;
    }
    return result;
}

std::string MirrorEncoderExecutor::encode(const std::string& message) const
{
    std::ostringstream ostream(std::ios_base::binary);
    for (auto ch : message)
    {
        auto c = static_cast<unsigned char>(ch);
        int digs = digits(c);
        ostream.put(digs);
        toBigEndian(ostream, mirror(c, digs));
    }
    return ostream.str();
}

std::string MirrorEncoderExecutor::decode(const std::string& message) const
{
    std::istringstream istream(message, std::ios_base::binary);
    std::string decoded;
    while (true)
    {
        unsigned char digs = istream.get();
        if (istream.fail())
            break;
        auto value = mirror(fromBigEndian<uint16_t>(istream), digs);
        if (istream.fail())
            break;
        decoded += static_cast<unsigned char>(value);
    }
    return decoded;
}
