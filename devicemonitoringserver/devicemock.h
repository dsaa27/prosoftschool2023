#ifndef DEVICE_H
#define DEVICE_H

#include "common.h"
#include <cstdint>
#include <string>
#include <vector>

//My include
#include "messages.h"
#include "encoderexecutor.h"
#include "messageencoder.h"

class AbstractClientConnection;

/*!
 * \brief Класс, эмитирующий устройство.
 */
class DeviceMock
{
    NON_COPYABLE(DeviceMock)
public:
    /*!
     * \brief Конструктор.
     * \param clientConnection - владеющий указатель на объект класса клиента
     */
    DeviceMock(AbstractClientConnection* clientConnection);
    ~DeviceMock();

    /*!
     * \brief Назначить устройству идентификатор.
     * \param deviceId - идентификатор устройства
     * \return false в случае ошибки
     */
    bool bind(uint64_t deviceId);
    /*!
     * \brief Подключить устройство к серверу.
     * \param serverId - идентификатор сревера
     * \return false в случае ошибки
     */
    bool connectToServer(uint64_t serverId);
    /*!
     * \brief Установить тестовый список измерений устройства.
     * \param measurements - список измерений
     */
    void setMeterages(std::vector<uint8_t> meterages);
    /*!
     * \brief Начать отправку измерений.
     */
    void startMeterageSending();



    /*!
     * \brief Добавить алгоритм, которым будут кодироваться и декодироваться сообщения
     */
    bool addEncodingAlgorithm(baseEncoderExecutor*);

    /*!
     * \brief Задать алгоритм, которым будут кодироваться и декодироваться сообщения
     */
    bool chooseEncodingAlgorithm(const std::string&);

private:
    /*!
     * \brief Отправить следующее измерение.
     */
    void sendNextMeterage();
    /*!
     * \brief Обработчик установления соединения.
     */
    void onConnected();
    /*!
     * \brief Обработчик разрыва соединения.
     */
    void onDisconnected();
    /*!
     * \brief Отправить сообщение.
     */
    void sendMessage(const std::string& message) const;
    /*!
     * \brief Обработчик получения нового сообщения от сервера.
     * \param message - сообщение
     */
    void onMessageReceived(const std::string& message);

private:
    AbstractClientConnection* m_clientConnection = nullptr;
    std::vector<uint8_t> m_meterages;
    uint64_t m_timeStamp = 0;

    //my fields
    messageEncoder msgEncoder;
    errorMessage* firstError;
    std::vector<int8_t> gotCommands;
};

#endif // DEVICE_H
