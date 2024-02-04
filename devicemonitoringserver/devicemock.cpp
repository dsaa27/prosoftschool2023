#include "devicemock.h"
#include "messagecommand.h"
#include "messageerror.h"
#include "messagemeterage.h"
#include <handlers/abstractaction.h>
#include <handlers/abstractmessagehandler.h>
#include <server/abstractclientconnection.h>

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

void DeviceMock::onMessageReceived(const std::string& message)
{
    if (!m_serializer.deserialize(m_encoder.decode(message),
                                  [this](const Message& message) {
        do
        {
            const MessageCommand* messageCommand = dynamic_cast<const MessageCommand*>(&message);
            if (messageCommand)
            {
                m_messages.push_back(std::unique_ptr<Message>(new MessageCommand(*messageCommand)));
                break;
            }
            const MessageError* messageError = dynamic_cast<const MessageError*>(&message);
            if (messageError)
            {
                m_messages.push_back(std::unique_ptr<Message>(new MessageError(*messageError)));
                break;
            }
            throw std::logic_error("Wrong message type!");
        } while (false);
    }))
        throw std::runtime_error("Message deserialization error!");
    sendNextMeterage(); // Отправляем следующее измерение
}

void DeviceMock::onConnected()
{
}

void DeviceMock::onDisconnected()
{
}

void DeviceMock::setMeterages(std::vector<uint8_t> meterages)
{
    m_meterages = std::move(meterages);
    m_timeStamp = 0;
}

void DeviceMock::startMeterageSending()
{
    sendNextMeterage();
}

const std::vector<std::unique_ptr<Message>>& DeviceMock::messages() const
{
    return m_messages;
}

MessageEncoder& DeviceMock::messageEncoder()
{
    return m_encoder;
}

void DeviceMock::sendNextMeterage()
{
    if (m_timeStamp >= m_meterages.size())
        return;
    const auto meterage = m_meterages.at(m_timeStamp);
    auto string = m_serializer.serialize(MessageMeterage(m_timeStamp, meterage));
    if (!string.empty())
    {
        sendMessage(m_encoder.encode(string));
        ++m_timeStamp;
    }
    else
        throw std::runtime_error("Message serialization error!");
}