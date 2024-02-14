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
    RUN_TEST(tr, encodeTest1);
    RUN_TEST(tr, serializeTestError);
    RUN_TEST(tr, serializeTestMeterage);
    RUN_TEST(tr, serializeTestCommand);
    RUN_TEST(tr, monitoringServerTest1);
    RUN_TEST(tr, monitoringServerNoScheduleTest);
    RUN_TEST(tr, monitoringServerNoTimestampTest);
    return 0;
}
