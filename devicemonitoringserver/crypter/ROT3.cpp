#include "ROT3.h"
#include <cstdint>

/* For first implementation skippping ignoring non-letter symbols
    Unsigned integer use "wrap around arifmetics"
*/

std::string ROT3Crypter::encode(const std::string& input) const {
    std::string output;
    for (u_int i = 0; i < input.length(); ++i) {
        output.push_back((static_cast<unsigned char>(input[0]) + 3));//ex[licitly using unsugned char just in case]
    }
    return output;
}

std::string ROT3Crypter::decode(const std::string& input) const {
    std::string output;
    for (u_int i = 0; i < input.length(); ++i) { 
        output.push_back((static_cast<unsigned char>(input[0]) - 3));//ex[licitly using unsugned char just in case]
    }
    return output;
}

std::string ROT3Crypter::name() const {
    
    return "ROT3"; //is it OK or is it implicit conversion
}