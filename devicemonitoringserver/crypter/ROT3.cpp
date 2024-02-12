#include "ROT3.h"
#include <cstdint>
#include <iostream>
#include <sstream>
#include <vector>

/* actually
    Unsigned integer use "wrap around arifmetics"
*/

std::string ROT3Crypter::encode(const std::string& input) const 

    std::istringstream inpStream(input);
    std::ostringstream out;
    std::string tmp;
    int tmp_int = 0;
    while (inpStream){
        inpStream >> tmp;
        tmp_int = std::stol(tmp);
        tmp_int += 3;
        out << tmp_int << ' ';
    }
    out << std::endl;
    return out.str();
}

std::string ROT3Crypter::decode(const std::string& input) const {

    std::istringstream inpStream(input);
    std::ostringstream out;
    std::string tmp;
    int tmp_int = 0;
    while (inpStream){
        inpStream >> tmp;
        tmp_int = std::stol(tmp);
        tmp_int -= 3;
        out << tmp_int << ' ';
    }
    out << std::endl;
    return out.str();

}

std::string ROT3Crypter::name() const {
    
    return "ROT3"; //is it OK or is it implicit conversion
}

/*
    std::istringstream inpStream(input);
    std::ostringstream out;
    std::string tmp;
    int tmp_int = 0;
    while (inpStream){
        inpStream >> tmp;
        tmp_int = std::stol(tmp);
        tmp_int -= 3;
        out << reflect(tmp_int) << ' ';
    }
    return out.str();
*/