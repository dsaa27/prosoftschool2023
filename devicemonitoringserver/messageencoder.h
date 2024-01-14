#ifndef MESSAGEENCODER_H
#define MESSAGEENCODER_H

#include <string>
#include <vector>

class BaseEncoderExecutor;

/*!
 * \brief Класс для шифрования сообщений
 */
class MessageEncoder
{
public:
    MessageEncoder();
    ~MessageEncoder();
    /*!
     * \brief Зашифровать сообщение \a message
     */
    std::string encode(const std::string& message);
    /*!
     * \brief Расшифровать сообщение \a message
     */
    std::string decode(const std::string& message);
    /*!
     * \brief Выбрать для шифрования алгоритм с названием \a name
     * \return false в случае ошибки
     */
    bool selectExecutor(const std::string& name);
    /*!
     * \brief Зарегистрировать алгоритм шифрования
     * \param executor - владеющий указатель на реализацию алгоритма шифрования
     * \return false в случае ошибки
     */
    bool addExecutor(BaseEncoderExecutor* executor);

private:
    BaseEncoderExecutor* m_currentExecutor = nullptr;
    std::vector<BaseEncoderExecutor*> m_executors;
};

#endif // MESSAGEENCODER_H