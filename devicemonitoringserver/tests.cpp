#include "tests.h"
#include "crypter/BitMirror.h"
#include "crypter/crypterBase.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "serialiZer/serializer.h"
#include "commandCenter/commandCenter.h"
#include "messages.h"
#include "test_runner.h"
#include <servermock/clientconnectionmock.h>
#include <servermock/connectionservermock.h>
#include <servermock/taskqueue.h>
#include <vector>
#include <random>
	

void monitoringServerTest1()
{
    // TODO: connection test - expect to recieve same amount of command as number of meterages
    TaskQueue taskQueue;
    
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));
    DeviceMock device(new ClientConnectionMock(taskQueue));

    const uint64_t deviceId = 42;
    const uint64_t serverId = 41;
    ASSERT(device.bind(deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    
    std::vector<uint8_t> newMeters;
    std::vector<unsigned int> expected;

    for (uint8_t i = 0; i < 50; ++i) {
        
        newMeters.push_back(i);
        expected.push_back(1);
    }
    ASSERT(server.setCrypter("NONE"));
    ASSERT(device.setCrypter("NONE"));
    device.setMeterages(newMeters);
    while (taskQueue.processTask())
        ;
    device.startMeterageSending();
    for (unsigned int d = 0; d < 150; ++d) {
        taskQueue.processTask();
    }
    std::vector<unsigned int> recieved = device.responces();
    ASSERT_EQUAL(device.responces().size(), expected.size());
}

void addEncoderTest()
{
    DeSerializer test_serial;
    Encoder test_encoder;
    MessageBase messageSrcStruct = {MsgType::Error, {0, 0}, ErrType::NoSchedule, 0};
    std::string messageSrc = test_serial.ToBytesArray(messageSrcStruct);
    ASSERT(test_encoder.addCrypter(new BitMirrorCrypter()));
    ASSERT(test_encoder.setCurrentCrypter("BitMirror"));
    std::string messageOutNewCrypt = test_encoder.decode(test_encoder.encode(messageSrc));
    ASSERT_EQUAL(messageSrc, messageOutNewCrypt);
}

void EncoderTest()
{

    DeSerializer test_serial;
    Encoder test_encoder;
    std::string messageSrc = test_serial.ToBytesArray({MsgType::Meterage, {65536, 15}, ErrType::NoErr, 0});
    ASSERT(test_encoder.setCurrentCrypter("ROT3"));
    std::string messageOutROT3 = test_encoder.decode(test_encoder.encode(messageSrc));

    ASSERT(test_encoder.setCurrentCrypter("Multiply41"));
    std::string messageOutM41 = test_encoder.decode(test_encoder.encode(messageSrc));
    ASSERT(test_encoder.setCurrentCrypter("Mirror"));
    std::string messageOutMirror = test_encoder.decode(test_encoder.encode(messageSrc));

    ASSERT_EQUAL(messageSrc, messageOutROT3);

    ASSERT_EQUAL(messageSrc, messageOutM41);

    ASSERT_EQUAL(messageSrc, messageOutMirror);
}

void serialiserTest()
{
    DeSerializer test_serial;

    MessageBase messageSrc = {MsgType::Meterage, {25687, 75}, ErrType::NoErr, 0};
    MessageBase messageOut = test_serial.ToMessage(test_serial.ToBytesArray(messageSrc));
    ASSERT_EQUAL(static_cast<u_int>(messageSrc.MessageType), static_cast<u_int>(messageOut.MessageType));
    ASSERT_EQUAL(messageSrc.data.timeStamp, messageOut.data.timeStamp);
    ASSERT_EQUAL(messageSrc.data.value, messageOut.data.value);

    messageSrc.error = ErrType::Obsolete;
    messageSrc.MessageType = MsgType::Error;
    MessageBase messageOut2 = test_serial.ToMessage(test_serial.ToBytesArray(messageSrc));
    ASSERT_EQUAL(static_cast<u_int>(messageSrc.MessageType), static_cast<u_int>(messageOut2.MessageType));
    ASSERT_EQUAL(static_cast<u_int>(messageSrc.error), static_cast<u_int>(messageOut2.error));

    messageSrc.MessageType = MsgType::Command;
    messageSrc.correction = -25;
    MessageBase messageOut3 = test_serial.ToMessage(test_serial.ToBytesArray(messageSrc));
    ASSERT_EQUAL(static_cast<u_int>(messageSrc.MessageType), static_cast<u_int>(messageOut3.MessageType));
    ASSERT_EQUAL(messageSrc.correction, messageOut3.correction);

}

void severalDeviceTest()
{
    // TODO: дописать тест
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMock device2(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = 111;
    const uint64_t serverId = 11;
    ASSERT(device.bind(deviceId));
    ASSERT(device2.bind(2*deviceId));
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    ASSERT(device2.connectToServer(serverId));

    std::vector<uint8_t> newMeters;
    std::vector<uint8_t> newMeters2;
    std::vector<unsigned int> expected;
    std::vector<unsigned int> expected2;
    std::vector<Phase> raspisanie;
    std::vector<Phase> raspisanie2;

    for (uint8_t i = 0; i < 50; ++i) {
        newMeters.push_back(i);
        newMeters2.push_back(2*i);
        
        if ((i+1)%3 == 0) {
            raspisanie.push_back(Phase{i, i}); 
            expected.push_back(1U);
        } else {
            expected.push_back(2U);
        }

        if (i%3 == 0) {
            raspisanie2.push_back(Phase{i, 2*i});
            expected2.push_back(1U);
        } else {
            expected2.push_back(2U);
        }
    }
    DeviceWorkSchedule const deviceWorkSchedule = {deviceId, raspisanie};
    DeviceWorkSchedule const deviceWorkSchedule2 = {2*deviceId, raspisanie2};

    ASSERT(server.setCrypter("Multiply41"));
    ASSERT(device.setCrypter("Multiply41"));
    ASSERT(device2.setCrypter("Multiply41"));

    device.setMeterages(newMeters);
    device2.setMeterages(newMeters2);

    server.setDeviceWorkSchedule(deviceWorkSchedule);
    server.setDeviceWorkSchedule(deviceWorkSchedule2);

    while (taskQueue.processTask())
        ;
    device.startMeterageSending();
    taskQueue.processTask();
    device2.startMeterageSending();
    while (taskQueue.processTask())
        ;

    std::vector<unsigned int> recieved = device.responces();
    std::vector<unsigned int> recieved2 = device2.responces();
    ASSERT_EQUAL(recieved.size(), expected.size());
    ASSERT_EQUAL(recieved2.size(), expected2.size());

    for(int i=0; i < expected.size(); ++i) {
        ASSERT_EQUAL(recieved[i], expected[i]);
        ASSERT_EQUAL(recieved2[i], expected2[i]);
    }

}

void commandCenterTest()
{
    // TODO: дописать тест
    CommandCenter test_commander;
    std::vector<Phase> raspisanie;
    MessageBase messageIn = {MsgType::Meterage, {5, 75}, ErrType::NoErr, 0};

    MessageBase responceExpect0 = {MsgType::Error, {0, 0}, ErrType::NoSchedule, 0};
    MessageBase responceExpect1 = {MsgType::Error, {0, 0}, ErrType::NoTimestamp, 0};
    MessageBase responceExpect2 = {MsgType::Command, {0, 0}, ErrType::NoErr, 25};
    MessageBase responceExpect3 = {MsgType::Error, {0, 0}, ErrType::Obsolete, 0};

    for (uint8_t i = 7; i < 50; ++i) {
        raspisanie.push_back(Phase{i, 2*i});
    }

    DeviceWorkSchedule const deviceWorkSchedule = {15, raspisanie};
    MessageBase responce0 = test_commander.acceptMessage(18, messageIn);

    ASSERT(test_commander.addDevice(deviceWorkSchedule));
    ASSERT(!test_commander.addDevice(deviceWorkSchedule));

    messageIn.data = {6, 1};
    MessageBase responce1 = test_commander.acceptMessage(15, messageIn);


    messageIn.data = {13, 1};
    MessageBase responce2 = test_commander.acceptMessage(15, messageIn);


    messageIn.data = {12, 1};
    MessageBase responce3 = test_commander.acceptMessage(15, messageIn);

    ASSERT_EQUAL(static_cast<u_int>(responceExpect2.MessageType), static_cast<u_int>(responce2.MessageType));
    ASSERT_EQUAL(responceExpect2.correction, responce2.correction);
   
    ASSERT_EQUAL(static_cast<u_int>(responceExpect0.MessageType), static_cast<u_int>(responce0.MessageType));
    ASSERT_EQUAL(static_cast<u_int>(responceExpect0.error), static_cast<u_int>(responce0.error));
    
    ASSERT_EQUAL(static_cast<u_int>(responceExpect1.MessageType), static_cast<u_int>(responce1.MessageType));
    ASSERT_EQUAL(static_cast<u_int>(responceExpect1.error), static_cast<u_int>(responce1.error));

    ASSERT_EQUAL(static_cast<u_int>(responceExpect3.MessageType), static_cast<u_int>(responce3.MessageType));
    ASSERT_EQUAL(static_cast<u_int>(responceExpect3.error), static_cast<u_int>(responce3.error));    
}


