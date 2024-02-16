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

    RUN_TEST(tr, serialiserTest);

    RUN_TEST(tr, EncoderTest);

    RUN_TEST(tr, addEncoderTest);

    RUN_TEST(tr, commandCenterTest);

    RUN_TEST(tr, monitoringServerTest1);   

    RUN_TEST(tr, severalDeviceTest);


    return 0;
}
