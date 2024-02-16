#include "devicemock.h"
#include <handlers/abstractaction.h>
#include <handlers/abstractmessagehandler.h>
#include <server/abstractclientconnection.h>

//My idea to include the lib
#include <iostream>
#include <string>
#include <utility>
#include "messages.h"
#include "messageserializator.h"


DeviceMock::DeviceMock(AbstractClientConnection* clientConnection) :
    m_clientConnection(clientConnection)
{
    struct ConnectedHandler : public AbstractAction
    {
    public:
        ConnectedHandler(DeviceMock* client) :
            m_client(client) {}
        void operator()() final
        {
            m_client->onConnected();
        }

    private:
        DeviceMock* m_client = nullptr;
    };
    m_clientConnection->setConnectedHandler(new ConnectedHandler(this));

    struct DisconnectedHandler : public AbstractAction
    {
    public:
        DisconnectedHandler(DeviceMock* client) :
            m_client(client) {}
        void operator()() final
        {
            m_client->onDisconnected();
        }

    private:
        DeviceMock* m_client = nullptr;
    };
    m_clientConnection->setDisconnectedHandler(new DisconnectedHandler(this));

    struct MessageHandler : public AbstractMessageHandler
    {
        MessageHandler(DeviceMock* client) :
            m_client(client) {}

    private:
        void operator()(const std::string& message) final
        {
            m_client->onMessageReceived(message);
        }

    private:
        DeviceMock* m_client = nullptr;
    };
    m_clientConnection->setMessageHandler(new MessageHandler(this));
}

DeviceMock::~DeviceMock()
{
    delete m_clientConnection;

    // Удалим ошибку, которая хранится в куче
    delete firstError;
}

bool DeviceMock::bind(uint64_t deviceId)
{
    return m_clientConnection->bind(deviceId);
}

bool DeviceMock::connectToServer(uint64_t serverId)
{
    return m_clientConnection->connectToHost(serverId);
}

void DeviceMock::sendMessage(const std::string& message) const
{
    m_clientConnection->sendMessage(message);
}

void DeviceMock::onMessageReceived(const std::string& msg /*message*/)
{
    //std::cout << "onMessageReceived (in device): " << msg << std::endl;
    // TODO: Разобрать std::string, прочитать команду,
    // записать ее в список полученных комманд

    std::string str = msgEncoder.decrypt(msg);
    std::pair<messageType, void*> p = messageSerializator::deserialize(str);
    
    switch(p.first) {
        case messageType::Command:
            {
                commandMessage* msg_ptr = reinterpret_cast<commandMessage*>(p.second);
                gotCommands.push_back(msg_ptr->_correctCommand);
                delete msg_ptr;
                sendNextMeterage(); // Отправляем следующее измерение
            }
            break;
        case messageType::Error:
            {
                firstError = reinterpret_cast<errorMessage*>(p.second);
                //Заканчиваем передачу, так как поймали ошибку
            }
            break;
    }  
}

void DeviceMock::onConnected()
{
    // TODO, если нужно
}

void DeviceMock::onDisconnected()
{
    // TODO, если нужно
}

void DeviceMock::setMeterages(std::vector<uint8_t> meterages)
{
    m_meterages = std::move(meterages);
}

void DeviceMock::startMeterageSending()
{
    sendNextMeterage();
}

void DeviceMock::sendNextMeterage()
{
    if (m_timeStamp >= m_meterages.size())
        return;
    const auto meterage = m_meterages.at(m_timeStamp);
    (void)meterage;
    //++m_timeStamp;
    // TODO: Сформировать std::string и передать в sendMessage

    meterageMessage* msg = new meterageMessage(m_timeStamp, meterage);
    std::string str = messageSerializator::serialize(msg);
    str = msgEncoder.encrypt(str);
    delete msg;
    ++m_timeStamp;
    sendMessage(str);
}

bool DeviceMock::addEncodingAlgorithm(baseEncoderExecutor* newCoder) {
    return msgEncoder.addCoder(newCoder);
}

bool DeviceMock::chooseEncodingAlgorithm(const std::string& str) {
    return msgEncoder.chooseCoder(str);
}
