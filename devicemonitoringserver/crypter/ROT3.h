#ifndef ROT3CRYPTER_H
#define ROT3CRYPTER_H

#include <string>
#include "crypter/absractCrypter.h"

/*!
 * \brief шифр цезаря - смещаем каждый символ на 3 и обратно. Наивная реалиция - нет фильтрации служебных символов т.к. знаем что все данные цифры.
 */
class ROT3Crypter : public BaseEncoderExecutor
{
public:
    ROT3Crypter() = default;
    ~ROT3Crypter() = default;
    /*!
     * \brief Метод шифровки - смещение на +3 .
     * \param input -  строка
     */
    std::string encode(const std::string& input) const final;
    /*!
     * \brief Метод дешифровки - смещение на -3 .
     * \param input -  строка
     */
    std::string decode(const std::string& input) const final;
    /*!
     * \brief Получение имени.
     */
    std::string name() const final;
};

#endif // ROT3CRYPTER_H