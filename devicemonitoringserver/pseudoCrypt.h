#ifndef CRYPT_H
#define CRYPT_H


class DemoCrypter {
public:
    const std::string decode(const std::string& message);
    const std::string encode(const std::string& message);
};

#endif