#ifndef ROT3CRYPTER_H
#define ROT3CRYPTER_H

#include <string>
#include "crypter/absractCrypter.h"

/*!
 * \brief заглушка шифродешифровщика, не делает ничего, нужна для дебага и amacriminal нешифрованного общения.
 */
class ROT3Crypter : public BaseEncoderExecutor
{
public:
    ROT3Crypter() = default;
    ~ROT3Crypter() = default;
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

#endif // ROT3CRYPTER_H