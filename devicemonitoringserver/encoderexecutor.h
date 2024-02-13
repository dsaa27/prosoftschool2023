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
    virtual ~baseEncoderExecutor(){}
};


class ROT3 final : public baseEncoderExecutor {
public:
    ROT3() {_name = "ROT3";}
    std::string encode (const std::string&);
    std::string decode (const std::string&);
    ~ROT3() override {}
};


class Mirror final : public baseEncoderExecutor {
public:
    Mirror() {_name = "Mirror";}
    std::string encode (const std::string&);
    std::string decode (const std::string&);
    ~Mirror() override {}
};


class Multiply41 final : public baseEncoderExecutor {
public:
    Multiply41() {_name = "Multiply41";}
    std::string encode (const std::string&);
    std::string decode (const std::string&);
    ~Multiply41() override {}
};

class Multiply5 final : public baseEncoderExecutor {
public:
    Multiply5() {_name = "Multiply5";}
    std::string encode (const std::string&);
    std::string decode (const std::string&);
    ~Multiply5() override {}
};

#endif //ENCODEREXECUTOR_H