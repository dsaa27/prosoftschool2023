#include "mirror.h"
#include <iostream>
#include <sstream>

std::string MirrorCrypter::encode(const std::string& input) const {
    return processString(input);
}

std::string MirrorCrypter::decode(const std::string& input) const {
    return processString(input);
}

std::string MirrorCrypter::name() const {
    std::string res = "Mirror";
    return res;
}

std::string MirrorCrypter::reflect(const std::string& input) const {
    std::string output; 
    if (input.empty()) return output;
    std::ostringstream out;
    unsigned int int_input = std::stol(input); //получаем беззнаковый инт, который надо развернуть
    
    /*план следующий - брать остаток от деления на 10, потом делить, пока не ноль.
    */
    // std::vector<unsigned int> reorder;
    while (int_input) {
        out << (int_input%10);
        int_input /= 10;
    }
    return out.str();
}

std::string MirrorCrypter::processString(const std::string& input) const {
    std::istringstream inpStream(input);
    std::ostringstream out;
    std::string tmp;
    while (inpStream){
        inpStream >> tmp;
        out << reflect(tmp) << ' ';
    }
    return out.str();
}