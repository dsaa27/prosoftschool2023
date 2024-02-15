#include "devicemonitoringserver.h"
#include <handlers/abstractaction.h>
#include <handlers/abstractmessagehandler.h>
#include <handlers/abstractnewconnectionhandler.h>
#include <server/abstractconnection.h>
#include <servermock/connectionservermock.h>

//My include
#include <iostream>
#include <string>
#include <utility>
#include "messages.h"
#include "messageserializator.h"

DeviceMonitoringServer::DeviceMonitoringServer(AbstractConnectionServer* connectionServer) :
    m_connectionServer(connectionServer)
{
    struct NewConnectionHandler : public AbstractNewConnectionHandler
    {
    public:
        NewConnectionHandler(DeviceMonitoringServer* server) :
            m_server(server) {}
        void operator()(AbstractConnection* conn) final
        {
            m_server->onNewIncomingConnection(conn);
        }

    private:
        DeviceMonitoringServer* m_server = nullptr;
    };
    m_connectionServer->setNewConnectionHandler(new NewConnectionHandler(this));
}

DeviceMonitoringServer::~DeviceMonitoringServer()
{
    delete m_connectionServer;
}

void DeviceMonitoringServer::setDeviceWorkSchedule(const DeviceWorkSchedule& sch)
{
    // TODO
    cm.addDeviceWorkSchedule(sch);
}

bool DeviceMonitoringServer::listen(uint64_t serverId)
{
    return m_connectionServer->listen(serverId);
}

void DeviceMonitoringServer::sendMessage(uint64_t deviceId, const std::string& message)
{
    auto* conn = m_connectionServer->connection(deviceId);
    if (conn)
        conn->sendMessage(message);
}

void DeviceMonitoringServer::onMessageReceived(uint64_t id/*deviceId*/, const std::string& msg/*message*/)
{
    // TODO
    //std::cout << "onMessageReceived (in server): " << msg << std::endl;

    //Расшифровка полученного сообщения
    std::string str = msgEncoder.decrypt(msg);
    std::pair<messageType, void*> p = messageSerializator::deserialize(str);
    meterageMessage* msg_ptr = reinterpret_cast<meterageMessage*>(p.second);
    p = cm.getNewMessage(id, msg_ptr->_timeStamp, msg_ptr->_meterage);
    delete msg_ptr;

    //Шифровка нового сообщения, полученного от commandCenter
    switch(p.first) {
        case messageType::Command:
            {
                commandMessage* msg_to_send = reinterpret_cast<commandMessage*>(p.second);
                str = messageSerializator::serialize(msg_to_send);
                delete msg_to_send;
                str = msgEncoder.encrypt(str);
            }
            break;
        case messageType::Error:
            {
                errorMessage* msg_to_send = reinterpret_cast<errorMessage*>(p.second);
                str = messageSerializator::serialize(msg_to_send);
                delete msg_to_send;
                str = msgEncoder.encrypt(str);
            }
            break;
    }


    sendMessage(id, str);
}

void DeviceMonitoringServer::onDisconnected(uint64_t /*clientId*/)
{
    // TODO, если нужен
}

void DeviceMonitoringServer::onNewIncomingConnection(AbstractConnection* conn)
{
    addMessageHandler(conn);
    addDisconnectedHandler(conn);
}

void DeviceMonitoringServer::addMessageHandler(AbstractConnection* conn)
{
    struct MessageHandler : public AbstractMessageHandler
    {
        MessageHandler(DeviceMonitoringServer* server, uint64_t clientId) :
            m_server(server), m_clientId(clientId) {}

    private:
        void operator()(const std::string& message) final
        {
            m_server->onMessageReceived(m_clientId, message);
        }

    private:
        DeviceMonitoringServer* m_server = nullptr;
        uint64_t m_clientId = 0;
    };
    const auto clientId = conn->peerId();
    conn->setMessageHandler(new MessageHandler(this, clientId));
}

void DeviceMonitoringServer::addDisconnectedHandler(AbstractConnection* conn)
{
    struct DisconnectedHandler : public AbstractAction
    {
        DisconnectedHandler(DeviceMonitoringServer* server, uint64_t clientId) :
            m_server(server), m_clientId(clientId) {}

    private:
        void operator()() final
        {
            m_server->onDisconnected(m_clientId);
        }

    private:
        DeviceMonitoringServer* m_server = nullptr;
        uint64_t m_clientId = 0;
    };
    const auto clientId = conn->peerId();
    conn->setDisconnectedHandler(new DisconnectedHandler(this, clientId));
}

bool DeviceMonitoringServer::addEncodingAlgorithm(baseEncoderExecutor* newCoder) {
    return msgEncoder.addCoder(newCoder);
}

bool DeviceMonitoringServer::chooseEncodingAlgorithm(const std::string& str) {
    return msgEncoder.chooseCoder(str);
}