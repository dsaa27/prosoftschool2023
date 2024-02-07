#ifndef MULTI41CRYPTER_H
#define MULTI41CRYPTER_H

#include <string>
#include "crypter/absractCrypter.h"

/*!
 * \brief заглушка шифродешифровщика, не делает ничего, нужна для дебага и amacriminal нешифрованного общения.
 */
class Multiply41Crypter : public BaseEncoderExecutor
{
public:
    Multiply41() = default;
    ~Multiply41() = default;
    /*!
     * \brief Метод как бы шифровки.
     * \param input -  строка
     */
    std::string encode(const std::string& input) const final;
    /*!
     * \brief Метод как бы дешифровки.
     * \param input -  строка
     */
    std::string decode(const std::string& input) const final;
    /*!
     * \brief Получение имени.
     */
    std::string name() const final;
};

#endif // MULTI41CRYPTER_H