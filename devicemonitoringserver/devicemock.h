#ifndef DEVICE_H
#define DEVICE_H

#include "common.h"
#include "cryptographer/encoder/encoder.h"
#include "serializer/serializer.h"
#include "message/messages.h"

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

    bool setCryptAlgorithm(std::string algName)
    {
        if (!m_crypt.algorithmExist(algName))
            return false;
        m_crypt.algorithmSet(algName);
    }

    std::vector<AbstractMessage*> getMsgLog() const
    {
        return m_msgLog;
    }

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
    Encoder m_crypt;
    Serializer m_serializer;
    std::vector<AbstractMessage*> m_msgLog;
};

#endif // DEVICE_H
