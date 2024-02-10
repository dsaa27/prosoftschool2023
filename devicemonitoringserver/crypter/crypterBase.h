#ifndef CRYPT_H
#define CRYPT_H

#include "absractCrypter.h"
#include "mirror.h"
#include "ROT3.h"
#include "Multiply41.h"
#include "stub.h"

#include <string>
#include <vector>
#include <map>


class Encoder {
public:
    Encoder();
    ~Encoder();
    const std::string decode(const std::string& message) ;
    const std::string encode(const std::string& message) ;
    bool crypterExist(const std::string& name);
    bool setCurrentCrypter(const std::string& name);
    bool addCrypter(BaseEncoderExecutor *);
private:
    std::vector<std::string> m_cryptersList = {"NONE","Mirrow","Multiply41","ROT3"};
    std::map<std::string, BaseEncoderExecutor*> m_crypterMap = {{"NONE", new StubCrypter()}, 
                                                                {"Mirrow", new MirrorCrypter()}, 
                                                                {"Multiply41", new Multiply41Crypter()}, 
                                                                {"ROT3", new ROT3Crypter()}};
    BaseEncoderExecutor* m_curr_Crypter = nullptr;
};

#endif