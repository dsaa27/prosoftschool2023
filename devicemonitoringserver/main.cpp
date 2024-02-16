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

    // TODO: собственные тесты:
    
    RUN_TEST(tr, messageSerializatorTest);
    RUN_TEST(tr, messageEncoderTest);
    RUN_TEST(tr, commandCenterTest);
    RUN_TEST(tr, wholeSystemTest);

    return 0;
}
