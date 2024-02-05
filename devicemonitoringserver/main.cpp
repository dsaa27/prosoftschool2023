#include "test_runner.h"
#include "tests.h"
#include <servermock/servertests.h>

int main()
{
    /*Just initial commit*/


    TestRunner tr;
    RUN_TEST(tr, taskQueueTest);
    RUN_TEST(tr, safeObjectPointerTest);
    RUN_TEST(tr, connectionChannelTest);
    RUN_TEST(tr, clientServerTest);

    // TODO: собственные тесты
    RUN_TEST(tr, monitoringServerTest1);
    return 0;
}
