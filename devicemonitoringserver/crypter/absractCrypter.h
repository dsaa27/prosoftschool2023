#ifndef ABSTRACTCRYPTER_H
#define ABSTRACTCRYPTER_H

#include <string>
#include "../messages.h"

/*!
 * \brief Базовый класс шифродешифровщика.
 */
class BaseEncoderExecutor
{
public:

    virtual ~BaseEncoderExecutor() = default;
    /*!
     * \brief Метод шифровки.
     * \param input - незашифрованная строка
     */
    virtual std::string encode(const std::string& input) const = 0;
    /*!
     * \brief Метод дешифровки.
     * \param input - зашифрованная строка
     */
    virtual std::string decode(const std::string& input) const = 0;
    /*!
     * \brief Получение имени.
     * \details шифровщики должны отличаться, и отличие должно быть видно при передаче. 
     *          но при этом абстрактный родитель не может иметь полей
     */
    virtual std::string name() const = 0;
};

#endif // ABSTRACTCRYPTER_H
