#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include <servermock/clientconnectionmock.h>
#include <servermock/connectionservermock.h>
#include <servermock/taskqueue.h>

//My include
#include "messageSerializator.h"
#include "encoderexecutor.h"
#include "messageencoder.h"
#include "commandcenter.h"

void monitoringServerTest1()
{
    
    // TODO: дописать тест
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = 111;
    const uint64_t serverId = 11;
    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    // device.setMeterages(  );
    // device.startMeterageSending();
    while (taskQueue.processTask())
        ;

    // ASSERT_EQUAL(device.responces(), expected);


}


void messageSerializatorTest() {

    ASSERT_EQUAL((messageSerializator::serialize(new meterageMessage(5, 45))), (std::string("0 5 45")))
    ASSERT_EQUAL((messageSerializator::serialize(new commandMessage(55))), (std::string("1 55")))
    ASSERT_EQUAL((messageSerializator::serialize(new errorMessage(errorType::NoSchedule))), (std::string("2 0")))

    meterageMessage* msg_ptr_1 = new meterageMessage(10, 15);
    std::pair<messageType, void*> p_1 = messageSerializator::deserialize("0 10 15");
    ASSERT_EQUAL(static_cast<int>(messageType::Meterage), static_cast<int>(p_1.first));
    meterageMessage* ret_ptr_1 = reinterpret_cast<meterageMessage*>(p_1.second);
    ASSERT_EQUAL(static_cast<int>(msg_ptr_1->_type), static_cast<int>(ret_ptr_1->_type))
    ASSERT_EQUAL(static_cast<int>(msg_ptr_1->_timeStamp), static_cast<int>(ret_ptr_1->_timeStamp))
    ASSERT_EQUAL(static_cast<int>(msg_ptr_1->_meterage), static_cast<int>(ret_ptr_1->_meterage))
    delete ret_ptr_1; delete msg_ptr_1;

    commandMessage* msg_ptr_2 = new commandMessage(33);
    std::pair<messageType, void*> p_2 = messageSerializator::deserialize("1 33");
    ASSERT_EQUAL(static_cast<int>(messageType::Command), static_cast<int>(p_2.first));
    commandMessage* ret_ptr_2 = reinterpret_cast<commandMessage*>(p_2.second);
    ASSERT_EQUAL(static_cast<int>(msg_ptr_2->_type), static_cast<int>(ret_ptr_2->_type))
    ASSERT_EQUAL(static_cast<int>(msg_ptr_2->_correctCommand), static_cast<int>(ret_ptr_2->_correctCommand))
    delete ret_ptr_2; delete msg_ptr_2;

    errorMessage* msg_ptr_3 = new errorMessage(errorType::NoTimeStamp);
    std::pair<messageType, void*> p_3 = messageSerializator::deserialize("2 1");
    ASSERT_EQUAL(static_cast<int>(messageType::Error), static_cast<int>(p_3.first));
    errorMessage* ret_ptr_3 = reinterpret_cast<errorMessage*>(p_3.second);
    ASSERT_EQUAL(static_cast<int>(msg_ptr_3->_type), static_cast<int>(ret_ptr_3->_type))
    ASSERT_EQUAL(static_cast<int>(msg_ptr_3->_error), static_cast<int>(ret_ptr_3->_error))
    delete ret_ptr_3; delete msg_ptr_3;
    
}

void messageEncoderTest() {
    messageEncoder coder;
    std::string rawStr = "Hello, World123.?!", decodedStr;

    ASSERT(coder.chooseCoder("ROT3"))
    decodedStr = coder.encrypt(rawStr);
    decodedStr = coder.decrypt(decodedStr);
    ASSERT_EQUAL(decodedStr, rawStr)


    ASSERT(coder.chooseCoder("Mirror"))
    decodedStr = coder.encrypt(rawStr);
    decodedStr = coder.decrypt(decodedStr);
    ASSERT_EQUAL(decodedStr, rawStr)

    ASSERT(coder.chooseCoder("Multiply41"))
    decodedStr = coder.encrypt(rawStr);
    decodedStr = coder.decrypt(decodedStr);
    ASSERT_EQUAL(decodedStr, rawStr)

    ASSERT(coder.addCoder(new Multiply5))
    ASSERT(coder.chooseCoder("Multiply5"))
    decodedStr = coder.encrypt(rawStr);
    decodedStr = coder.decrypt(decodedStr);
    ASSERT_EQUAL(decodedStr, rawStr)
}

void commandCenterTest() {

    commandCenter cm;
    uint64_t deviceid = 123;
    DeviceWorkSchedule sch = { deviceid,
                                {
                                    {0, 12},
                                    {1, 25},
                                    {2, 10},
                                    {3, 15},
                                    {4, 55}
                                }};

    //Проверка правильной записи нового плана
    ASSERT(cm.addDeviceWorkSchedule(sch))
    ASSERT_EQUAL(cm.addDeviceWorkSchedule(sch), false)
    
    //Проверка возвращения commandMessage
    commandMessage* msg_ptr_1 = new commandMessage(-3);
    std::pair<messageType, void*> p_1 = cm.getNewMessage(deviceid, 0, 15);
    ASSERT_EQUAL(static_cast<int>(messageType::Command), static_cast<int>(p_1.first));
    commandMessage* ret_ptr_1 = reinterpret_cast<commandMessage*>(p_1.second);
    ASSERT_EQUAL(static_cast<int>(msg_ptr_1->_type), static_cast<int>(ret_ptr_1->_type))
    ASSERT_EQUAL(static_cast<int>(msg_ptr_1->_correctCommand), static_cast<int>(ret_ptr_1->_correctCommand))
    delete ret_ptr_1; delete msg_ptr_1;

    //Проверка возвращения commandMessage
    commandMessage* msg_ptr_2 = new commandMessage(10);
    std::pair<messageType, void*> p_2 = cm.getNewMessage(deviceid, 1, 15);
    ASSERT_EQUAL(static_cast<int>(messageType::Command), static_cast<int>(p_2.first));
    commandMessage* ret_ptr_2 = reinterpret_cast<commandMessage*>(p_2.second);
    ASSERT_EQUAL(static_cast<int>(msg_ptr_2->_type), static_cast<int>(ret_ptr_2->_type))
    ASSERT_EQUAL(static_cast<int>(msg_ptr_2->_correctCommand), static_cast<int>(ret_ptr_2->_correctCommand))
    delete ret_ptr_2; delete msg_ptr_2;

    //Проверка возвращения errorMessage (NoSchedule)
    errorMessage* msg_ptr_3 = new errorMessage(errorType::NoSchedule);
    std::pair<messageType, void*> p_3 = cm.getNewMessage(deviceid + 1, 1, 15);
    ASSERT_EQUAL(static_cast<int>(messageType::Error), static_cast<int>(p_3.first));
    errorMessage* ret_ptr_3 = reinterpret_cast<errorMessage*>(p_3.second);
    ASSERT_EQUAL(static_cast<int>(msg_ptr_3->_type), static_cast<int>(ret_ptr_3->_type))
    ASSERT_EQUAL(static_cast<int>(msg_ptr_3->_error), static_cast<int>(ret_ptr_3->_error))
    delete ret_ptr_3; delete msg_ptr_3;

    //Проверка возвращения errorMessage (NoTimeStamp)
    errorMessage* msg_ptr_4 = new errorMessage(errorType::NoTimeStamp);
    std::pair<messageType, void*> p_4 = cm.getNewMessage(deviceid, 15, 15);
    ASSERT_EQUAL(static_cast<int>(messageType::Error), static_cast<int>(p_4.first));
    errorMessage* ret_ptr_4 = reinterpret_cast<errorMessage*>(p_4.second);
    ASSERT_EQUAL(static_cast<int>(msg_ptr_4->_type), static_cast<int>(ret_ptr_4->_type))
    ASSERT_EQUAL(static_cast<int>(msg_ptr_4->_error), static_cast<int>(ret_ptr_4->_error))
    delete ret_ptr_4; delete msg_ptr_4;

    //Проверка возвращения errorMessage (Obsolete)
    errorMessage* msg_ptr_5 = new errorMessage(errorType::Obsolete);
    std::pair<messageType, void*> p_5 = cm.getNewMessage(deviceid, 0, 15);
    ASSERT_EQUAL(static_cast<int>(messageType::Error), static_cast<int>(p_5.first));
    errorMessage* ret_ptr_5 = reinterpret_cast<errorMessage*>(p_5.second);
    ASSERT_EQUAL(static_cast<int>(msg_ptr_5->_type), static_cast<int>(ret_ptr_5->_type))
    ASSERT_EQUAL(static_cast<int>(msg_ptr_5->_error), static_cast<int>(ret_ptr_5->_error))
    delete ret_ptr_5; delete msg_ptr_5;
}

void wholeSystemTest() {
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    //Связывание сервера и датчика
    const uint64_t deviceId = 111;
    const uint64_t serverId = 11;
    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));

    //Задание планов для сервера и дачтика
    DeviceWorkSchedule sch = { deviceId,
                                {
                                    {0, 12},
                                    {1, 25},
                                    {2, 10},
                                    {3, 15},
                                    {4, 55}
                                }};
    device.setMeterages( {12, 20, 15, 15, 90} );
    server.setDeviceWorkSchedule(sch);

    //Задание алгоритмов шифрования
    ASSERT(device.addEncodingAlgorithm(new Multiply5))
    ASSERT(device.chooseEncodingAlgorithm("Multiply5"))
    ASSERT(server.addEncodingAlgorithm(new Multiply5))
    ASSERT(server.chooseEncodingAlgorithm("Multiply5"))

    //Запуск процесса обмена сообщениями
    device.startMeterageSending();
    while (taskQueue.processTask())
        ;

}

