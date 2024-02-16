#include "Multiply41.h"
#include <cstdint>

std::string Multiply41Crypter::encode(const std::string& input) const {
    std::string output;
    unsigned int result = 0;
    unsigned int part1 = 0;
    unsigned int part2 = 0;
    for (u_int i = 0; i < input.length(); ++i) {
        result = 41 * ((input[i])); // 0 to 6 will reult in MSB being 0 but it should be OK
        part1 = result >> 8;
        part2 = result & 0xFF;
        output.push_back(part1);
        output.push_back(part2);
    }
    return output;
}

std::string Multiply41Crypter::decode(const std::string& input) const {
    std::string output;
    uint16_t result = 0;
    for (u_int i = 0; i < input.length(); ++i) { //assuming that input.length is always even with this crypter
        result = (((input[i] << 8) + input[i+1])/41);
        i++;
        output.push_back(static_cast<unsigned int>(result));
    }
    return output;
}

std::string Multiply41Crypter::name() const {
    
    return "Multiply41"; //is it OK or is it implicit conversion
}