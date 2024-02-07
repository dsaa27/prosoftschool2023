#include "Multiply41.h"
#include <cstdint>

std::string Multiply41Crypter::encode(const std::string& input) const {
    std::string output;
    uint16_t result = 0;
    for (int i = 0; i < input.length(); ++i) {
        result = 41 * (static_cast<int>(input[i])); // 0 to 6 will reult in MSB being 0 but it should be OK
        output.push_back(static_cast<char>(result >> 8));
        output.push_back(static_cast<char>(result & 0x0F));
    }
    return output;
}

std::string Multiply41Crypter::decode(const std::string& input) const {
    std::string output;
    uint16_t result = 0;
    for (int i = 0; i < input.length(); ++i) { //assuming that input.length is always even with this crypter
        result = ((input[i] << 8) + input[++i])/21;
        output.push_back(static_cast<char>(result));
    }
    return output;
}

std::string Multiply41Crypter::name() const {
    
    return "Multiply41"; //is it OK or is it implicit conversion
}