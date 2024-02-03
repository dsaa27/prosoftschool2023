#ifndef MESSAGESERIALIZER_H
#define MESSAGESERIALIZER_H

#include <functional>
#include <string>

class Message;

/*!
 * \brief Класс для сериализации сообщений
 */
class MessageSerializer
{
public:
    /*!
     * \brief Сериализовать сообщение \a message
     */
    std::string serialize(const Message& message) const;
    /*!
     * \brief Десериализовать сообщение
     * \param string - строка с сообщением
     * \param callback - коллбэк для обработки десериализованного сообщения
     * \return false в случае ошибки
     */
    bool deserialize(const std::string& string, std::function<void(const Message&)> callback) const;
};

#endif // MESSAGESERIALIZER_H