#ifndef DEVICE_H
#define DEVICE_H

#include "common.h"
#include "messageprocessors/messageencoder.h"
#include "messageprocessors/messageserializator.h"
#include "encodingmodule.h"
#include <string>
#include <vector>

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
     * \brief Установить шифрующий модуль на устройство
     * \param encoder - шифрующий модуль
     */
    void setEncodingModule(EncodingModule* encoder);
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
     * \brief Посмотреть команды, полученные от устройства.
     */
    const std::vector<std::string>& getReceivedCommands();
    /*!
     * \brief Начать отправку измерений.
     */
    void startMeterageSending();

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
    EncodingModule* m_encoder = nullptr;
    std::vector<std::string> m_commands;
};

#endif // DEVICE_H
