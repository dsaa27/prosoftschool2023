#ifndef MIRROCRYPTER_H
#define MIRROCRYPTER_H

#include <string>
#include "crypter/absractCrypter.h"

/*!
 * \brief заглушка шифродешифровщика, не делает ничего, нужна для дебага и amacriminal нешифрованного общения.
 */
class MirrorCrypter : public BaseEncoderExecutor 
{
public:
    MirrorCrypter() = default;
    ~MirrorCrypter() = default;
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

private: 
    std::string reflect(const std::string& input) const;
};

#endif // MIRROCRYPTER_H