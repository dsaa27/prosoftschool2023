#include "multiply41encoderexecutor.h"
#include "bigendian.h"

#include <cstdint>
#include <sstream>

std::string Multiply41EncoderExecutor::encode(const std::string& message)
{
    std::ostringstream ostream(std::ios_base::binary);
    for (auto ch : message)
    {
        auto c = static_cast<unsigned char>(ch);
        toBigEndian(ostream, static_cast<uint16_t>(c * 41));
    }
    return ostream.str();
}

std::string Multiply41EncoderExecutor::decode(const std::string& message)
{
    std::istringstream istream(message, std::ios_base::binary);
    std::string decoded;
    while (true)
    {
        auto value = fromBigEndian<uint16_t>(istream);
        if (istream.fail())
            break;
        decoded += static_cast<unsigned char>(value / 41);
    }
    return decoded;
}
