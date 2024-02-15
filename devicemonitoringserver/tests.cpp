#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include <servermock/clientconnectionmock.h>
#include <servermock/connectionservermock.h>
#include <servermock/taskqueue.h>
#include <cryptographer/encoder/encoder.h>
#include <serializer/serializer.h>
#include <message/messages.h>
#include <commandcenter/commandcenter.h>
#include <iostream>

void encodeTest1()
{
    Encoder encoder;
    encoder.algorithmSet("ROT3");
    std::string CODE = "123";
    ASSERT_EQUAL(CODE, "123");

    std::string CRYPT_CODE = encoder.encode(CODE);
    ASSERT_EQUAL(CRYPT_CODE, "456");

    std::string DECRYPT_CODE = encoder.decode(CRYPT_CODE);
    ASSERT_EQUAL(DECRYPT_CODE, "123");

}

void serializeTestMeterage()
{
    MeterageMessage msg(10, 10);
    Serializer ser;
    ASSERT_EQUAL(ser.serialize(&msg), "0 10 10");
    std::string str = ser.serialize(&msg);
    AbstractMessage* msg2 = ser.deserialize(str);
    ASSERT_EQUAL(ser.serialize(msg2), "0 10 10");
}

void serializeTestError()
{
    ErrorMessage msg(ErrorMessage::ErrorType::Obsolete);
    Serializer ser;
    ASSERT_EQUAL(ser.serialize(&msg), "2 2");
    std::string str = ser.serialize(&msg);
    AbstractMessage* msg2 = ser.deserialize(str);
    ASSERT_EQUAL(ser.serialize(msg2), "2 2");
}

void serializeTestCommand()
{
    CommandMessage msg(12);
    Serializer ser;
    ASSERT_EQUAL(ser.serialize(&msg), "1 12");
    std::string str = ser.serialize(&msg);
    AbstractMessage* msg2 = ser.deserialize(str);
    ASSERT_EQUAL(ser.serialize(msg2), "1 12");
}
//
//void monitoringServerTest1()
//{
//    // TODO: дописать тест
//    TaskQueue taskQueue;
//    DeviceMock device(new ClientConnectionMock(taskQueue));
//    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));
//
//    const uint64_t deviceId = 111;
//    const uint64_t serverId = 11;
//    ASSERT(device.bind(deviceId));
//    ASSERT(server.listen(serverId));
//    ASSERT(device.connectToServer(serverId));
//    // device.setMeterages(  );
//    // device.startMeterageSending();
//    while (taskQueue.processTask())
//        ;
//
//    // ASSERT_EQUAL(device.responces(), expected);
//}

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

    std::vector<Phase> schedulePhase;
    std::vector<uint8_t> devicePlaningPhase;
    for (uint8_t i = 0; i < 5; ++i)
    {
        Phase temp1 = { i, i + 2 };
        schedulePhase.push_back(temp1);
        devicePlaningPhase.push_back(i + 1);
    }
    DeviceWorkSchedule const deviceWorkSchedule = { deviceId, schedulePhase };
    server.setDeviceWorkSchedule(deviceWorkSchedule);
    device.setMeterages(devicePlaningPhase);
    
    while (taskQueue.processTask());


    device.startMeterageSending();

    // ASSERT_EQUAL(device.responces(), expected);
}

void monitoringServerNoScheduleTest()
{
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = 111;
    const uint64_t serverId = 11;
    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    std::vector<uint8_t> meterages { 1, 2, 3 };
    device.setMeterages(meterages);
    device.startMeterageSending();
    while (taskQueue.processTask());
    std::vector<AbstractMessage*> msgLog = device.getMsgLog();

    for (size_t i = 0; i < msgLog.size(); ++i)
    {
        ErrorMessage* msg = dynamic_cast<ErrorMessage*>(msgLog[i]);
        ErrorMessage::ErrorType q = (msg)->getErrorType();
        ASSERT_EQUAL((int)ErrorMessage::ErrorType::NoSchedule, (int)q);

    }
}

void monitoringServerNoTimestampTest()
{
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = 111;
    const uint64_t serverId = 11;
    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    std::vector<uint8_t> meterages { 1, 2, 3, 4, 5 };

    std::vector<Phase> schedulePhase = {
        { 0, 1 },
        { 1, 2 },
        { 2, 3 }
    };
    DeviceWorkSchedule const deviceWorkSchedule = { deviceId, schedulePhase };
    server.setDeviceWorkSchedule(deviceWorkSchedule);

    device.setMeterages(meterages);
    while (taskQueue.processTask())
    device.startMeterageSending();
    while (taskQueue.processTask());
    std::vector<AbstractMessage*> msgLog = device.getMsgLog();
        ;

    for (size_t i = 0; i < 3; ++i)
    {
        AbstractMessage::MessageType msgType = msgLog[i]->getMessageType();
        AbstractMessage::MessageType q = AbstractMessage::MessageType::Command;
        ASSERT_EQUAL((int)msgType, (int)q);
    }

    for (size_t i = 3; i < 5; ++i)
    {
        ErrorMessage* msg = dynamic_cast<ErrorMessage*>(msgLog[i]);
        ErrorMessage::ErrorType q = (msg)->getErrorType();
        ASSERT_EQUAL((int)ErrorMessage::ErrorType::NoTimestamp, (int)q);
    }
}
