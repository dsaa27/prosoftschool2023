#include "mirror.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>

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

int MirrorCrypter::reflect(int int_input) const {
    if (int_input / 10 == 0) return int_input; //число с одним разрядом есть зеркало самого себя
    std::vector<int> temp;
    int out = 0;
    /*план следующий - брать остаток от деления на 10, потом делить, пока не ноль.
    */
    // std::vector<unsigned int> reorder;
    while (int_input) {
        temp.push_back(int_input%10);
        int_input /= 10;
    }
    int size = temp.size();
    for(int i = 0 ;i < size; ++i)
    {
        out += temp[size-i-1] * (static_cast<int>(std::pow(10, i)));
    }
    
    return out;
}

std::string MirrorCrypter::processString(const std::string& input) const {
    std::istringstream inpStream(input);
    std::ostringstream out;
    std::string tmp;
    int tmp_int = 0;
    int test_int = 0;
    bool naiveCheck = false;
    while (inpStream) {
        inpStream >> tmp;
        if (tmp.empty()) break;
        tmp_int = std::stol(tmp);
        test_int = reflect(tmp_int);
        if (naiveCheck) {
            out << ' ' << reflect(tmp_int);
        } else {
            out << reflect(tmp_int);
        }            
        naiveCheck = true;
        tmp.clear();
    }
    // std::string tmp2 = out.str();
    out << std::endl;
    std::string tmp2 = out.str();
    return out.str();
}