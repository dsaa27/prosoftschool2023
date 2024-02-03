#ifndef STUBCRYPTER_H
#define STUBCRYPTER_H

#include <string>
#include "crypter/absractCrypter.h"

/*!
 * \brief заглушка шифродешифровщика, не делает ничего, нужна для дебага и amacriminal нешифрованного общения.
 */
class StubCrypter : public AbstractCrypter
{
public:
    Stub() = default;
    ~Stub() = default;
    /*!
     * \brief Метод как бы шифровки.
     * \param input -  строка
     */
    std::string encode(const std::string& input) const;
    /*!
     * \brief Метод как бы дешифровки.
     * \param input -  строка
     */
    std::string decode(const std::string& input) const;
    /*!
     * \brief Получение имени.
     */
    std::string name() const;
};

#endif // STUBCRYPTER_H