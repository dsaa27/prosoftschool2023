#include "tests.h"
#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include <servermock/clientconnectionmock.h>
#include <servermock/connectionservermock.h>
#include <servermock/taskqueue.h>
#include <vector>

void monitoringServerTest1()
{
    // TODO: дописать тест
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
    std::vector<Phase> raspisanie;
    for (unsigned int i = 0; i < 100; ++i) {
        
        newMeters.push_back(i);
        expected.push_back(2U);
        raspisanie.push_back(Phase{i, i/2 });
    }
    DeviceWorkSchedule const deviceWorkSchedule = {deviceId, raspisanie};
    server.setDeviceWorkSchedule(deviceWorkSchedule);
    ASSERT(server.setCrypter("ROT3"));
    ASSERT(device.setCrypter("ROT3"));
    device.setMeterages(newMeters);
    // device.startMeterageSending();

    while (taskQueue.processTask())
        ;
    device.startMeterageSending();
    for (unsigned int d = 0; d < 250; ++d) {
        taskQueue.processTask();
    }
    std::vector<unsigned int> recieved = device.responces();
    // for(int i = 0; i < 100; ++i) {
        // std::cerr <<expected[i] <<std::endl;
    // }
    ASSERT_EQUAL(device.responces().size(), expected.size());
}

void EncoderTest()
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



}

void addEncoderTest()
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

}

void serialiserTest()
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

}

void severalDeviceTest()
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

}

void servAnswerTest()
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

}


