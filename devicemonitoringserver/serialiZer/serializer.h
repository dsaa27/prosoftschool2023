#ifndef SERDESER_H
#define SERDESER_H

#include <string>
#include <iostream>
#include "../messages.h"

class DeSerializer {

public:
    /*!
     * \brief Расфасовка дешифрованной строки по полям структуры
     * \param messageStr - строка, содержащая значения, разделённые '\r'
     * \retval Заполненная структура сообщения
     */
    MessageBase ToMessage(const std::string& messageStr);

    /*!
     * \brief создание строки из значений полей структуры сообщений
     * \param message - Заполненная структура сообщения
     * \retval строка, содержащая значения, разделённые '\r'
     */
    std::string ToBytesArray(const MessageBase& message);
};

#endif