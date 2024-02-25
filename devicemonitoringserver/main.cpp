#include "test_runner.h"
#include "tests.h"
#include <servermock/servertests.h>

int main()
{
    TestRunner tr;
    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);

    // TODO: собственные тесты
    RUN_TEST(tr, deviceIdBindingTest);
    RUN_TEST(tr, messageEqualOperatorTest);
    RUN_TEST(tr, messageSerializatorSerializeTest);
    RUN_TEST(tr, messageSerializatorDeserializeTest);
    RUN_TEST(tr, messageSerializatorInverseSerializatorTest);
    RUN_TEST(tr, messageEncoderROT3Test);
    RUN_TEST(tr, messageEncoderMirrorTest);
    RUN_TEST(tr, messageEncoderMultiply41Test);
    RUN_TEST(tr, messageEncoderMultyEncodingTest);
    RUN_TEST(tr, messageEncoderCustomAlgorithmTest);
    RUN_TEST(tr, commandCenterErrorReturningTest);
    RUN_TEST(tr, commandCenterCommandReturningTest);
    RUN_TEST(tr, commandCenterMultipleDeviceServeTest);
    RUN_TEST(tr, monitoringServerSimpleTest);
    RUN_TEST(tr, monitoringServerNoScheduleTest);
    RUN_TEST(tr, monitoringServerDifferentMessageTest);
    RUN_TEST(tr, monitoringServerManyDevicesTest);
    RUN_TEST(tr, monitoringServerChaosTest);
    return 0;
}
