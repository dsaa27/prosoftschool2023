#include "crypterBase.h"
#include <string>
#include <vector>
#include <map>
#include <utility>

Encoder::Encoder() {
    m_cryptersList.push_back("NONE");
    m_curr_Crypter = m_crypterMap[m_cryptersList(0)];
}

Encoder::~Encoder(){
    while (!m_cryptersList.empty()) {
        delete m_crypterMap[m_cryptersList[0]];
        m_crypterMap.erase(m_cryptersList[0]);
        m_cryptersList.erase(0);
    }
}

const std::string Encoder::decode(const std::string& message){
    return m_curr_Crypter->decode(message); 
}

const std::string Encoder::encode(const std::string& message){
    
    return m_curr_Crypter->encode(message);
}

bool Encoder::crypterExist(const std::string& name) {
    if (m_crypterMap.find(name) == m_crypterMap.end()) return false;
    return true;
}

bool Encoder::setCurrentCrypter (const std::string& name)
{
    if (!crypterExist(name)) return false; //can't set non-existing crypter as default
    m_curr_Crypter = m_crypterMap[name];
    return true;
}

bool Encoder::addCrypter (BaseEncoderExecutor *newCrypter)
{
    if (crypterExist(newCrypter->name())) return true; //consider already existing crypter a success for now
    m_crypterMap.insert(std::make_pair(newCrypter->name(), newCrypter));
    return true;
}


