#include "BitMirror.h"

std::string BitMirrorCrypter::encode(const std::string& input) const {
    return reflect(input);
}

std::string BitMirrorCrypter::decode(const std::string& input) const {
    return reflect(input);
}

std::string BitMirrorCrypter::name() const {
    std::string res = "BitMirror";
    return res;
}

std::string BitMirrorCrypter::reflect(const std::string& input) const {
    std::string output; 
    if (input.empty()) return output;
    output.resize(input.length());
    for (u_int i = 0; i < input.length(); ++i) {
        unsigned int lobmys = 0;
        unsigned int symbol = input[i];
        
        lobmys += (symbol & 0x80) >> 7;
        lobmys += (symbol & 0x40) >> 5;
        lobmys += (symbol & 0x20) >> 3;
        lobmys += (symbol & 0x10) >> 1;
        lobmys += (symbol & 0x08) << 1;
        lobmys += (symbol & 0x04) << 3;
        lobmys += (symbol & 0x02) << 5;
        lobmys += (symbol & 0x01) << 7;
        
        output[i] = lobmys;
    }
    return output;
}