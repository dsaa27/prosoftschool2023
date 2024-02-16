#include "ROT3.h"
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

/* actually
    Unsigned integer use "wrap around arifmetics"
*/

std::string ROT3Crypter::encode(const std::string& input) const 
{
    std::istringstream inpStream(input);
    std::ostringstream out;
    std::string tmp;
    int tmp_int = 0;
    out.clear();
    bool naiveCheck = false;
    while (inpStream) {
        inpStream >> tmp;
        if (tmp.empty()) break;
        for(int i = 0; i<tmp.length(); ++i) {
            tmp[i] += 3;
        }
        if (naiveCheck) {
            out << ' ' << tmp;
        } else {
            out << tmp;
        }            
        naiveCheck = true;
        tmp.clear();
    }
    out << std::endl;
    return out.str();
}

std::string ROT3Crypter::decode(const std::string& input) const {

    std::istringstream inpStream(input);
    std::ostringstream out;
    std::string tmp;
    int tmp_int = 0;
    bool naiveCheck = false;
    while (inpStream) {
        inpStream >> tmp;
        if (tmp.empty()) break;

        for(int i = 0; i<tmp.length(); ++i) {
            tmp[i] -= 3;
        }
        if (naiveCheck) {
            out << ' ' << tmp;
        } else {
            out << tmp;
        }
        naiveCheck = true;
        tmp.clear();
    }
    out << std::endl;
    return out.str();
}

std::string ROT3Crypter::name() const {
    
    return std::string("ROT3"); 
}
