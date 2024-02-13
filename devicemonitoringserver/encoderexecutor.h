#ifndef ENCODEREXECUTOR_H
#define ENCODEREXECUTOR_H

#include <string>

class baseEncoderExecutor {

protected:
    std::string _name;

public:
    virtual std::string encode (const std::string&) = 0;
    virtual std::string decode (const std::string&) = 0;
    std::string name() const {return _name;}
};


class ROT3 final : public baseEncoderExecutor {
public:
    ROT3() {_name = "ROT3";}
    std::string encode (const std::string&) ;
    std::string decode (const std::string&) ;
};


class Mirror final : public baseEncoderExecutor {
public:
    Mirror() {_name = "Mirror";}
    std::string encode (const std::string&) ;
    std::string decode (const std::string&) ;
};


class Multiply41 final : public baseEncoderExecutor {
public:
    Multiply41() {_name = "Multiply41";}
    std::string encode (const std::string&) ;
    std::string decode (const std::string&) ;
};

class Multiply5 final : public baseEncoderExecutor {
public:
    Multiply5() {_name = "Multiply5";}
    std::string encode (const std::string&) ;
    std::string decode (const std::string&) ;
};

#endif //ENCODEREXECUTOR_H