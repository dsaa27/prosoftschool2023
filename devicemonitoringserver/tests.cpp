#include "tests.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "messageserializator.h"
#include "messageencoder.h"
#include "test_runner.h"
#include <servermock/clientconnectionmock.h>
#include <servermock/connectionservermock.h>
#include <servermock/taskqueue.h>
#include <cstddef>

void messageSerializatorSerializeTest()
{
	std::string expected = "command 12";
	Command command(12);
	std::string serializeCommand = MessageSerializator::serialize(command);
	ASSERT_EQUAL(serializeCommand, expected);

	expected = "meterage 12 15";
	Meterage meterage(12, 15);
	std::string serializeMeterage = MessageSerializator::serialize(meterage);
	ASSERT_EQUAL(serializeMeterage, expected);

	expected = "error NoTimestamp";
	Error error(ErrorType::NoTimestamp);
	std::string serializeError = MessageSerializator::serialize(error);
	ASSERT_EQUAL(serializeError, expected);

	expected = "error NoSchedule";
	Error error1(ErrorType::NoSchedule);
	std::string serializeError1 = MessageSerializator::serialize(error1);
	ASSERT_EQUAL(serializeError1, expected);

	expected = "error Obsolete";
	Error error2(ErrorType::Obsolete);
	std::string serializeError2 = MessageSerializator::serialize(error2);
	ASSERT_EQUAL(serializeError2, expected);
}


void messageSerializatorDeserializeTest()
{
	std::string serializeMeterage = "meterage 12 15";
	pMeterage meterage =
		std::static_pointer_cast<Meterage>(MessageSerializator::deserialize(serializeMeterage));
	Meterage expected(12, 15);
	ASSERT_EQUAL(meterage->getMeterage(), expected.getMeterage());
	ASSERT_EQUAL(meterage->getTimeStamp(), expected.getTimeStamp());

	std::string serializeCommand = "command 16";
	pCommand command =
		std::static_pointer_cast<Command>(MessageSerializator::deserialize(serializeCommand));
	Command expected1(16);
	ASSERT_EQUAL(command->getAdjustment(), expected1.getAdjustment());

	std::string serializeError = "error NoTimestamp";
	pError error =
		std::static_pointer_cast<Error>(MessageSerializator::deserialize(serializeError));
	Error expected2(ErrorType::NoTimestamp);
	ASSERT_EQUAL(error->getErrorType(), expected2.getErrorType());

	serializeError = "error NoSchedule";
	error =
		std::static_pointer_cast<Error>(MessageSerializator::deserialize(serializeError));
	expected2 = ErrorType::NoSchedule;
	ASSERT_EQUAL(error->getErrorType(), expected2.getErrorType());

	serializeError = "error Obsolete";
	error =
		std::static_pointer_cast<Error>(MessageSerializator::deserialize(serializeError));
	expected2 = ErrorType::Obsolete;
	ASSERT_EQUAL(error->getErrorType(), expected2.getErrorType());
}

void messageEncoderEncodeROT3Test()
{
	std::string serializeMessage = "command 34 78";
	std::string encodedMessage = MessageEncoder::instance().encode(serializeMessage);
	std::string expected = "frppdqg#67#:;";
	ASSERT_EQUAL(encodedMessage, expected);
}

void messageEncoderDecodeROT3Test()
{
	std::string serializeEncodeedMessage = "huuru#Revrohwh";
	std::string decodedMessage = MessageEncoder::instance().decode(serializeEncodeedMessage);
	std::string expected = "error Obsolete";
	ASSERT_EQUAL(decodedMessage, expected);
}

void monitoringServerNoScheduleTest()
{
	TaskQueue taskQueue;
	DeviceMock device(new ClientConnectionMock(taskQueue));
	DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

	const uint64_t deviceId = 222;
	const uint64_t serverId = 22;
	ASSERT(device.bind(deviceId));
	ASSERT(server.listen(serverId));
	ASSERT(device.connectToServer(serverId));
	std::vector<uint8_t> meterages{0,1,2,3,4,5};
	device.setMeterages(meterages);
	while (taskQueue.processTask())
		device.startMeterageSending();
		;
	std::vector<pAbstractMessage> messageHistory = device.getMessageHistory();
	std::vector<Error> expected {Error(ErrorType::NoSchedule),
								 Error(ErrorType::NoSchedule),
								 Error(ErrorType::NoSchedule),
								 Error(ErrorType::NoSchedule),
								 Error(ErrorType::NoSchedule),
								 Error(ErrorType::NoSchedule)};
	for (size_t i = 0; i < messageHistory.size(); ++i)
	{
		Error message = *std::static_pointer_cast<Error>(messageHistory[i]).get();
		ASSERT(message == expected[i]);
	}
}

void monitoringServerNoTimeStampTest()
{
	TaskQueue taskQueue;
	DeviceMock device(new ClientConnectionMock(taskQueue));
	DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

	const uint64_t deviceId = 222;
	const uint64_t serverId = 22;
	ASSERT(device.bind(deviceId));
	ASSERT(server.listen(serverId));
	ASSERT(device.connectToServer(serverId));
	std::vector<uint8_t> meterages{0,1,2,3,4,5};
	device.setMeterages(meterages);
	DeviceWorkSchedule deviceWorkSchedule{.deviceId = 222};
	server.setDeviceWorkSchedule(deviceWorkSchedule);
	while (taskQueue.processTask())
	{
		device.startMeterageSending();
	}
	std::vector<pAbstractMessage> messageHistory = device.getMessageHistory();
	std::vector<Error> expected {Error(ErrorType::NoTimestamp),
								 Error(ErrorType::NoTimestamp),
								 Error(ErrorType::NoTimestamp),
								 Error(ErrorType::NoTimestamp),
								 Error(ErrorType::NoTimestamp),
								 Error(ErrorType::NoTimestamp)};
	for (size_t i = 0; i < messageHistory.size(); ++i)
	{
		Error message = *std::static_pointer_cast<Error>(messageHistory[i]).get();
		ASSERT(message == expected[i]);
	}
}

void monitoringServerCommandTest()
{
	TaskQueue taskQueue;
	DeviceMock device(new ClientConnectionMock(taskQueue));
	DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

	const uint64_t deviceId = 222;
	const uint64_t serverId = 22;
	ASSERT(device.bind(deviceId));
	ASSERT(server.listen(serverId));
	ASSERT(device.connectToServer(serverId));
	std::vector<uint8_t> meterages{0,1,2,3,4,5};
	device.setMeterages(meterages);
	std::vector<Phase> phases{{0,2},{1,3},{2,3},{3,4},{4,96},{5,76}};
	DeviceWorkSchedule deviceWorkSchedule{.deviceId = 222, .schedule = phases};
	server.setDeviceWorkSchedule(deviceWorkSchedule);
	while (taskQueue.processTask())
	{
		device.startMeterageSending();
	}
	std::vector<pAbstractMessage> messageHistory = device.getMessageHistory();
	std::vector<Command> expected {Command(2), Command(2), Command(1), Command(1),
		Command(92), Command(71)};
	for (size_t i = 0; i < messageHistory.size(); ++i)
	{
		Command message = *std::static_pointer_cast<Command>(messageHistory[i]).get();
		ASSERT(message == expected[i]);
	}
}

void monitoringServerCommandTwoDevicesTest()
{
	TaskQueue taskQueue;
	DeviceMock device1(new ClientConnectionMock(taskQueue));
	DeviceMock device2(new ClientConnectionMock(taskQueue));

	DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

	const uint64_t deviceId1 = 222;
	const uint64_t deviceId2 = 2222;
	const uint64_t serverId = 22;

	ASSERT(device1.bind(deviceId1));
	ASSERT(device2.bind(deviceId2));

	ASSERT(server.listen(serverId));

	ASSERT(device1.connectToServer(serverId));
	ASSERT(device2.connectToServer(serverId));


	std::vector<uint8_t> meterages1{0,1,2,3,4,5};
	device1.setMeterages(meterages1);
	std::vector<Phase> phases1{{0,2},{1,3},{2,3},{3,4},{4,96},{5,76}};
	DeviceWorkSchedule deviceWorkSchedule1{.deviceId = deviceId1, .schedule = phases1};

	std::vector<uint8_t> meterages2{0,8,100,5,56,8,};
	device2.setMeterages(meterages2);
	std::vector<Phase> phases2{{0,5},{1,13},{2,7},{3,56},{4,96},{5,76}};
	DeviceWorkSchedule deviceWorkSchedule2{.deviceId = deviceId2, .schedule = phases2};

	server.setDeviceWorkSchedule(deviceWorkSchedule1);
	server.setDeviceWorkSchedule(deviceWorkSchedule2);

	while (taskQueue.processTask())
	{

	}

	device1.startMeterageSending();
	device2.startMeterageSending();

	while (taskQueue.processTask())
	{

	}
	std::vector<pAbstractMessage> messageHistory1 = device1.getMessageHistory();
	std::vector<pAbstractMessage> messageHistory2 = device2.getMessageHistory();
	std::vector<Command> expected1 {Command(2), Command(2), Command(1), Command(1),
		Command(92), Command(71)};
	std::vector<Command> expected2 {Command(5), Command(5), Command(-93), Command(51),
		Command(40), Command(68)};
	for (size_t i = 0; i < messageHistory1.size(); ++i)
	{
		Command message = *std::static_pointer_cast<Command>(messageHistory1[i]).get();
		ASSERT(message == expected1[i]);
	}
	for (size_t i = 0; i < messageHistory2.size(); ++i)
	{
		Command message = *std::static_pointer_cast<Command>(messageHistory2[i]).get();
		ASSERT(message == expected2[i]);
	}
}
