#ifndef CRYPT_H
#define CRYPT_H
#include <string>
#include <vector>
#include "absractCrypter.h"
#include "mirror.h"

#include "stub.h"

// class Crypter {
// public:
//     const std::string decode(const std::string& message, const std::string& decoder);
//     const std::string encode(const std::string& message, const std::string& encoder);
// };
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
    std::vector<std::string> m_cryptersList;
    std::map<std::string, BaseEncoderExecutor*> m_crypterMap = {{"NONE", new Stub()}, {"Mirrow", new MirrorCrypter()}};
    BaseEncoderExecutor* m_curr_Crypter = nullptr;
};

#endif