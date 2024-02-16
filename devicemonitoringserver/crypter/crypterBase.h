#ifndef CRYPT_H
#define CRYPT_H

#include "absractCrypter.h"
#include "mirror.h"
#include "ROT3.h"
#include "Multiply41.h"
#include "stub.h"

#include <string>
#include <vector>
#include <map>


class Encoder {
public:

    Encoder();

    ~Encoder();

    /*!
     * \brief дешифрование строки текущим методом шифрования
     * \param message - зашифрованная строка сообщения
     * \retval дешифрованная строка сообщения
     */
    const std::string decode(const std::string& message) ;

    /*!
     * \brief Шифрование строки текущим методом шифрования
     * \param message - дешифрованная строка сообщения
     * \retval зашифрованная строка сообщения 
     */
    const std::string encode(const std::string& message) ;

    /*!
     * \brief проверка существования какого либо метода шифровка по его названию
     * \param name - Название метода шифрования /Например, Mirror
     * \retval true если есть такой метод
     */
    bool crypterExist(const std::string& name);

    /*!
     * \brief установка текущего метода шифроки
     * \param name - Название метода шифрования /Например, Mirror
     * \retval true если установили метод успешно
     */
    bool setCurrentCrypter(const std::string& name);

    /*!
     * \brief Добавление нового метода шифрования
     * \param crypter - abstract base class pointer, указывающий на новый класс-шифровщик
     *                  унаследованный от BaseEncoderExecutor
     * \retval флаг успеха попытки
     */
    bool addCrypter(BaseEncoderExecutor * crypter);

private:
    // std::vector<std::string> m_cryptersList = {"NONE","Mirror","Multiply41","ROT3"};
    std::map<std::string, BaseEncoderExecutor*> m_crypterMap = {{"NONE", new StubCrypter()}, 
                                                                {"Mirror", new MirrorCrypter()}, 
                                                                {"Multiply41", new Multiply41Crypter()}, 
                                                                {"ROT3", new ROT3Crypter()}};
    BaseEncoderExecutor* m_curr_Crypter = nullptr;
};

#endif