#ifndef DEVICEMONITORINGSERVER_H
#define DEVICEMONITORINGSERVER_H

#include "common.h"

#include <cstdint>
#include <string>
#include "deviceworkschedule.h"
#include "commandcenter.h"
#include "messageprocessors/messageencoder.h"
#include "encodingmodule.h"

struct DeviceWorkSchedule;
class AbstractConnectionServer;
class AbstractConnection;

/*!
 * \brief Класс сервера для мониторинга состояния устройств.
 */
class DeviceMonitoringServer
{
    NON_COPYABLE(DeviceMonitoringServer)
public:
    /*!
     * \brief Конструктор.
     * \param connectionServer - владеющий указатель на сервер для приема подключений
     */
    DeviceMonitoringServer(AbstractConnectionServer* connectionServer);
    ~DeviceMonitoringServer();

    /*!
     * \brief Установить план работы устройств.
     */
    void setDeviceWorkSchedule(const DeviceWorkSchedule&, uint64_t deviceID);
    /*!
     * \brief Установить шифрующий модуль на сервер
     * \param encoder - шифрующий модуль
     */
    void setEncodingModule(EncodingModule* encoder);
    /*!
     * \brief Привязать сервер к командному центру
     * \param comandCenter - командный центр
     */
    void bindComandCenter(CommandCenter* comandCenter);
    /*!
     * \brief Начать прием подключений по идентификатору \a serverId
     */
    bool listen(uint64_t serverId);

private:
    /*!
     * \brief Отправить сообщение устройству.
     * \param deviceId - идентификатор устройства
     * \param message - сообщение
     */
    void sendMessage(uint64_t deviceId, const std::string& message);
    /*!
     * \brief Обработчик приема нового сообщения от устройства.
     * \param deviceId - идентификатор устройства
     * \param message - сообщение
     */
    void onMessageReceived(uint64_t deviceId, const std::string& message);
    /*!
     * \brief Обработчик поступления нового входящего подключения.
     * \param conn - невладеющий указатель на объект подключения
     */
    void onNewIncomingConnection(AbstractConnection* conn);
    /*!
     * \brief Обработчик разрыва соединения.
     * \param deviceId - идентификатор устройства
     */
    void onDisconnected(uint64_t clientId);

private:
    void addMessageHandler(AbstractConnection* conn);
    void addDisconnectedHandler(AbstractConnection* conn);

private:
    AbstractConnectionServer* m_connectionServer = nullptr;
    EncodingModule* m_encoder=nullptr;
    CommandCenter* m_comandCenter=nullptr;
};

#endif // DEVICEMONITORINGSERVER_H
