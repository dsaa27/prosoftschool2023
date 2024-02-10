#include "mirror.h"

std::string MirrorCrypter::encode(const std::string& input) const {
    return reflect(input);
}

std::string MirrorCrypter::decode(const std::string& input) const {
    return reflect(input);
}

std::string MirrorCrypter::name() const {
    std::string res = "Mirror";
    return res;
}

std::string MirrorCrypter::reflect(const std::string& input) const {
    std::string output; 
    if (input.empty()) return output;
    output.resize(input.length());
    for (u_int i = 0; i < input.length(); ++i) {
        char lobmys = 0;
        char symbol = input[i];
        
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