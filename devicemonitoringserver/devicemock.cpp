
#include "devicemock.h"
#include "common.h"
#include "handlers/abstractaction.h"
#include "handlers/abstractmessagehandler.h"
#include "server/abstractclientconnection.h"

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
// TODO: Разобрать std::string, прочитать команду,
    // записать ее в список полученных комманд
    /*

    мюсли жокера
    1. проверяем на эмпти
    2. кастуем первый символ к енуму типов сообщений
        2.1 по результатам создаём нужный инстанс сообщения и заполняем
        2.2 видимо аппендим этот инстанс в контейнер полученных сообщение 
            (тут хз это же долбануто огромный лог, хотя может по меркам десктопа норм)
            этот пункт должен перехать в комманд центр сервера и там нам как бы пофиг на ресурсы
            
        
    */
    MessageBase messageStruct = m_DeSerial.ToMessage(m_crypter.decode(message));
    m_commandLog.push_back(messageStruct.MessageType);
    sendNextMeterage(); // Отправляем следующее измерение
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
    // (void)meterage; //kinda need to know what it is. what c-style cast to void(and not void * ) does;
    ++m_timeStamp;
    MessageBase messageOut = {MsgType::Meterage, {0,0}, ErrType::NoErr, 0};
    messageOut.data.timeStamp = m_timeStamp;
    messageOut.data.value = meterage;
    std::string messageStr = m_crypter.encode(m_DeSerial.ToBytesArray(messageOut));
    sendMessage(messageStr);
    // TODO: Сформировать std::string и передать в sendMessage

}
