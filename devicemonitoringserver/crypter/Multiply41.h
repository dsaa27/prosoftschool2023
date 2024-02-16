#ifndef MULTI41CRYPTER_H
#define MULTI41CRYPTER_H

#include <string>
#include "crypter/absractCrypter.h"

/*!
 * \brief Умножение на 41 - каждый чар превращается в 2 байта. .
 */
class Multiply41Crypter : public BaseEncoderExecutor
{
public:
    Multiply41Crypter() = default;
    ~Multiply41Crypter() = default;
    /*!
     * \brief Метод шифровки - умножение.
     * \param input -  строка
     */
    std::string encode(const std::string& input) const final;
    /*!
     * \brief Метод дешифровки - формирование uint16 и деление .
     * \param input -  строка
     */
    std::string decode(const std::string& input) const final;
    /*!
     * \brief Получение имени.
     */
    std::string name() const final;
};

#endif // MULTI41CRYPTER_H