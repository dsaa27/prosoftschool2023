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
	RUN_TEST(tr, monitoringServerCommandTest);
	RUN_TEST(tr, monitoringServerCommandTwoDevicesTest);
	RUN_TEST(tr, monitoringServerNoTimeStampTest);
	RUN_TEST(tr,monitoringServerNoScheduleTest);
	RUN_TEST(tr, messageSerializatorSerializeTest);
	RUN_TEST(tr, messageSerializatorDeserializeTest);
	RUN_TEST(tr, messageEncoderEncodeROT3Test);
	RUN_TEST(tr, messageEncoderDecodeROT3Test);
    return 0;
}
