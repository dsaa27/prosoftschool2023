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
     * \brief Метод шифровки сменой порядка десятичных разрядов кажого числа в сообщении.
     * \param input -  строка
     */
    std::string encode(const std::string& input) const final;
    /*!
     * \brief Метод дешифровки сменой порядка десятичных разрядов кажого числа в сообщении.
     * \param input -  строка
     */
    std::string decode(const std::string& input) const final;
    /*!
     * \brief Получение имени.
     */
    std::string name() const final;

private: 
    /*!
     * \brief поразрядное отзеркаливание строки (в строке должен быть 1 инт)
     * \param input -входящая строка из 1го числа
     * \retval "Отзеркаленная" строка из 1го числа
     */
    std::string reflect(const std::string& input) const;

    /*!
     * \brief поразрядное отзеркаливание каждого байта в строке методом reflect
     * \param input -входящая строка
     * \retval "Отзеркаленная" строка
     */
    std::string processString(const std::string& input) const;
};

#endif // MIRROCRYPTER_H