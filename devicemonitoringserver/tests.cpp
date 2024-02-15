#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include <servermock/clientconnectionmock.h>
#include <servermock/connectionservermock.h>
#include <servermock/taskqueue.h>
#include <cryptographer/encoder/encoder.h>
#include <cryptographer/algorithms/multiply41.h>
#include <serializer/serializer.h>
#include <message/messages.h>
#include <commandcenter/commandcenter.h>
#include <iostream>

void encodeTestSwitch()
{
    Encoder encoder;
    ASSERT(encoder.algorithmExist("MULTIPLY41"));
    ASSERT(encoder.algorithmSet("MULTIPLY41"));
    ASSERT(encoder.algorithmSettedUp());
    ASSERT(dynamic_cast<Multiply41Crypt*>(encoder.algorithmCurrent()));
}

void encodeTestDefault()
{
    // DEFAULT - ROT3, SO TEST ROT3
    Encoder encoder;
    std::string CODE = "123";
    ASSERT_EQUAL(CODE, "123");

    std::string CRYPT_CODE = encoder.encode(CODE);
    ASSERT_EQUAL(CRYPT_CODE, "456");

    std::string DECRYPT_CODE = encoder.decode(CRYPT_CODE);
    ASSERT_EQUAL(DECRYPT_CODE, "123");

}

void encodeTestMultiply41()
{
    // DEFAULT - ROT3, SO TEST ROT3
    Encoder encoder;
    // '!' = 33, '\1' = 1, ')' = 41, '~' = 126, 'R' = 82, '{' = 123, 'y' = 121
    std::string CODE = "1234aAzZ!\1)~R{y";
    ASSERT_EQUAL(CODE, "1234aAzZ!\1)~R{y");

    ASSERT(encoder.algorithmSet("MULTIPLY41"));

    std::string CRYPT_CODE = encoder.encode(CODE);

    // if char * 41 is negative, add 128 (MAX_CHAR + 1)
    char c1 = static_cast<char>(static_cast<int>('1') * 41 + 128);
    char c2 = static_cast<char>(static_cast<int>('2') * 41);
    char c3 = static_cast<char>(static_cast<int>('3') * 41);
    char c4 = static_cast<char>(static_cast<int>('4') * 41);
    char c5 = static_cast<char>(static_cast<int>('a') * 41 + 128);
    char c6 = static_cast<char>(static_cast<int>('A') * 41);
    char c7 = static_cast<char>(static_cast<int>('z') * 41 + 128);
    char c8 = static_cast<char>(static_cast<int>('Z') * 41);
    char c9 = static_cast<char>(static_cast<int>('!') * 41);
    char c10 = static_cast<char>(static_cast<int>('\1') * 41);
    char c11 = static_cast<char>(static_cast<int>(')') * 41 + 128);
    char c12 = static_cast<char>(static_cast<int>('~') * 41);
    char c13 = static_cast<char>(static_cast<int>('R') * 41);
    char c14 = static_cast<char>(static_cast<int>('{') * 41 + 128);
    char c15 = static_cast<char>(static_cast<int>('y') * 41);
    char c[16] = { c1, c2, c3, c4, c5, c6, c7, c8, c9, c10, c11, c12, c13, c14, c15 };

    std::string c_str = c;
    ASSERT_EQUAL(CRYPT_CODE, c_str);

    std::string DECRYPT_CODE = encoder.decode(CRYPT_CODE);
    ASSERT_EQUAL(DECRYPT_CODE, "1234aAzZ!\1)~R{y");
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
        { 2, 3 },
        { 4, 5 }
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

    for (size_t i = 3; i < 4; ++i)
    {
        ErrorMessage* msg = dynamic_cast<ErrorMessage*>(msgLog[i]);
        ErrorMessage::ErrorType q = (msg)->getErrorType();
        ASSERT_EQUAL((int)ErrorMessage::ErrorType::NoTimestamp, (int)q);
    }

    for (size_t i = 4; i < 5; ++i)
    {
        AbstractMessage::MessageType msgType = msgLog[i]->getMessageType();
        AbstractMessage::MessageType q = AbstractMessage::MessageType::Command;
        ASSERT_EQUAL((int)msgType, (int)q);
    }
}
