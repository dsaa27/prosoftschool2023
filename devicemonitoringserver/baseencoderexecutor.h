#ifndef BASEENCODEREXECUTOR_H
#define BASEENCODEREXECUTOR_H

#include <string>

/*!
 * \brief Абстрактный базовый класс для алгоритмов шифрования
 */
class BaseEncoderExecutor
{
public:
    virtual ~BaseEncoderExecutor() = default;
    /*!
     * \brief Зашифровать сообщение \a message
     */
    virtual std::string encode(const std::string& message) = 0;
    /*!
     * \brief Расшифровать сообщение \a message
     */
    virtual std::string decode(const std::string& message) = 0;
    /*!
     * \brief Название алгоритма
     */
    virtual std::string name() const = 0;
};

#endif // BASEENCODEREXECUTOR_H