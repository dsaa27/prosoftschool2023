




#include "test_runner.h"
#include "tests.h"
#include <servermock/servertests.h>

/*
//my include
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include <servermock/clientconnectionmock.h>
#include <servermock/connectionservermock.h>
#include <servermock/taskqueue.h>
*/





int main()
{
    /*
    TestRunner tr;
    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);

    // TODO: собственные тесты
    RUN_TEST(tr, monitoringServerTest1);
    */


   /*
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    const uint64_t deviceId = 111;
    const uint64_t serverId = 11;

    server.listen(serverId);

    device.bind(deviceId);
    device.setMeterages({1, 2, 3});
    device.connectToServer(serverId);

    device.startMeterageSending();

    while (taskQueue.processTask())
        ;
    
    std::cout << "Done" << std::endl;
    */


    TestRunner tr;
    RUN_TEST(tr, messageSerializatorTest);
    RUN_TEST(tr, messageEncoderTest);

    return 0;
}
