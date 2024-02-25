#include "tests.h"
#include "message/errormessage.h"
#include "message/commandmessage.h"
#include "message/meteragemessage.h"
#include "messageprocessors/messageserializator.h"
#include "messageprocessors/messageencoder.h"
#include "devicemock.h"
#include "devicemonitoringserver.h"
#include "test_runner.h"
#include <servermock/clientconnectionmock.h>
#include <servermock/connectionservermock.h>
#include <servermock/connectionchannel.h>
#include <servermock/taskqueue.h>
#include "encodingmodule.h"
#include "commandcenter.h"

void deviceIdBindingTest()
{
    TaskQueue taskQueue;
    DeviceMock device1(new ClientConnectionMock(taskQueue));
    DeviceMock device2(new ClientConnectionMock(taskQueue));
    DeviceMock device3(new ClientConnectionMock(taskQueue));
    ASSERT(device1.bind(5));
    ASSERT(device2.bind(6));
    ASSERT(!device3.bind(5));
}

void messageEqualOperatorTest()
{
    ErrorMessage error1(ErrorMessage::ErrorType::NoSchedule);
    ErrorMessage error2(ErrorMessage::ErrorType::NoSchedule);
    ErrorMessage error3(ErrorMessage::ErrorType::NoTimestamp);
    CommandMessage command1(-50);
    CommandMessage command2(-50);
    CommandMessage command3(60);
    MeterageMessage meterage1(1, 50);
    MeterageMessage meterage2(1, 50);
    MeterageMessage meterage3(2, 50);
    MeterageMessage meterage4(1, 80);
    ASSERT(error1 == error2);
    ASSERT(error1 != error3);
    ASSERT(command1 == command2);
    ASSERT(command1 != command3);
    ASSERT(meterage1 == meterage2);
    ASSERT(meterage1 != meterage3);
    ASSERT(meterage1 != meterage4);
}

void messageSerializatorSerializeTest()
{
    ErrorMessage error(ErrorMessage::ErrorType::NoSchedule);
    CommandMessage command(-50);
    MeterageMessage meterage(1, 50);

    std::string answerForError = "Error;NoSchedule;";
    std::string answerForCommand = "Command;-50;";
    std::string answerForMeterage = "Meterage;1;50;";

    ASSERT_EQUAL(MessageSerializator::serializeMessage(error), answerForError);
    ASSERT_EQUAL(MessageSerializator::serializeMessage(command), answerForCommand);
    ASSERT_EQUAL(MessageSerializator::serializeMessage(meterage), answerForMeterage);
}

void messageSerializatorDeserializeTest()
{
    std::string error = "Error;NoSchedule;";
    std::string command = "Command;-50;";
    std::string meterage = "Meterage;1;50;";

    ErrorMessage answerForError(ErrorMessage::ErrorType::NoSchedule);
    CommandMessage answerForCommand(-50);
    MeterageMessage answerForMeterage(1, 50);
    ASSERT_EQUAL(MessageSerializator::deserializeErrorMessage(error), answerForError);
    ASSERT_EQUAL(MessageSerializator::deserializeCommandMessage(command), answerForCommand);
    ASSERT_EQUAL(MessageSerializator::deserializeMeterageMessage(meterage), answerForMeterage);
}

void messageSerializatorInverseSerializatorTest()
{
    std::string errorString = "Error;NoSchedule;";
    std::string commandString = "Command;-50;";
    std::string meterageString = "Meterage;1;50;";

    ErrorMessage errorMessage(ErrorMessage::ErrorType::NoSchedule);
    CommandMessage commandMessage(-50);
    MeterageMessage meterageMessage(1, 50);
    
    ASSERT_EQUAL(MessageSerializator::deserializeErrorMessage(MessageSerializator::serializeMessage(errorMessage)), errorMessage);
    ASSERT_EQUAL(MessageSerializator::deserializeCommandMessage(MessageSerializator::serializeMessage(commandMessage)), commandMessage);
    ASSERT_EQUAL(MessageSerializator::deserializeMeterageMessage(MessageSerializator::serializeMessage(meterageMessage)), meterageMessage);

    ASSERT_EQUAL(MessageSerializator::serializeMessage(MessageSerializator::deserializeErrorMessage(errorString)), errorString);
    ASSERT_EQUAL(MessageSerializator::serializeMessage(MessageSerializator::deserializeCommandMessage(commandString)), commandString);
    ASSERT_EQUAL(MessageSerializator::serializeMessage(MessageSerializator::deserializeMeterageMessage(meterageString)), meterageString);
}

void messageEncoderROT3Test()
{
    MessageEncoder encoder;
    std::string input({0x30, 0x40, 0x50});
    std::string out({ 0x33, 0x43, 0x53 });
    ASSERT_EQUAL(encoder.encode(input, encoder.chooseAlgorithm("ROT3")), out);
    ASSERT_EQUAL(encoder.decode(out, encoder.chooseAlgorithm("ROT3")), input);
}

void messageEncoderMirrorTest()
{
    MessageEncoder encoder;
    std::string input({ 56, 123, 127, (char)255 });
    std::string out({ 0x00, 0x00, 0x41, 0x00, 0x01, 0x41, 0x00, 0x02, (char)0xD1, 0x00, 0x02, 0x28 });
    ASSERT_EQUAL(encoder.encode(input, encoder.chooseAlgorithm("Mirror")), out);
    ASSERT_EQUAL(encoder.decode(out, encoder.chooseAlgorithm("Mirror")), input);
}

void messageEncoderMultiply41Test()
{
    MessageEncoder encoder;
    std::string input({2, 56, 123, 127, (char)255 });
    std::string out({ 0x00, 0x52, 0x08, (char)0xF8, 0x13, (char)0xB3, 0x14, 0x57, 0X28, (char)0XD7});
    ASSERT_EQUAL(encoder.encode(input, encoder.chooseAlgorithm("Multiply41")), out);
    ASSERT_EQUAL(encoder.decode(out, encoder.chooseAlgorithm("Multiply41")), input);
}

void messageEncoderMultyEncodingTest()
{
    MessageEncoder encoder;
    std::string input({ 30, 40, 50 });
    std::string out({ 0, 0, 0, 0, 0x05, 0x49, 0, 0, 0, 0, 0x05, 0x72, 0, 0, 0, 0, 0x05, (char)0x9B });
    ASSERT_EQUAL(encoder.encode(
                    encoder.encode(
                        encoder.encode(
                            input,
                            encoder.chooseAlgorithm("ROT3")),
                        encoder.chooseAlgorithm("Mirror")),
                     encoder.chooseAlgorithm("Multiply41")), out);

    ASSERT_EQUAL(encoder.decode(
                    encoder.decode(
                        encoder.decode(
                            out,
                            encoder.chooseAlgorithm("Multiply41")),
                        encoder.chooseAlgorithm("Mirror")),
                    encoder.chooseAlgorithm("ROT3")), input);
}

void messageEncoderCustomAlgorithmTest()
{
    class Xor15_20_25 final : public BaseEncoderExecutor 
    {
    public:
        Xor15_20_25() :
            BaseEncoderExecutor("Xor15_20_25") {}

        std::string encode(const std::string& str) const override
        {
            std::string answer(str);
            for (auto& sim : answer)
            {
                sim=sim ^ 15 ^ 20 ^ 25;
            }
            return answer;
        }

        std::string decode(const std::string& str) const override
        {
            std::string answer(str);
            for (auto& sim : answer)
            {
                sim = sim ^ 25 ^ 20 ^ 15;
            }
            return answer;
        }

        Xor15_20_25* clone() const override
        {
            return new Xor15_20_25();
        }
    };

    MessageEncoder encoder;
    ASSERT_EQUAL(encoder.chooseAlgorithm("Xor15_20_25"), nullptr)
    encoder.registerAlgorithm(new Xor15_20_25);
    std::string input({ 10, 20, 30 });
    std::string out({ 8, 22, 28 });
    ASSERT_EQUAL(encoder.encode(input, encoder.chooseAlgorithm("Xor15_20_25")), out);
    ASSERT_EQUAL(encoder.decode(out, encoder.chooseAlgorithm("Xor15_20_25")), input);
}

void commandCenterErrorReturningTest()
{
    CommandCenter::reset();
    using errorType = ErrorMessage::ErrorType;
    using messageType=Message::MessageType;
    EncodingModule encoder = EncodingModule(MessageEncoder(), "Mirror");
    DeviceWorkSchedule fakeSchedule, emptySchedule, tardlyTimeStampSchedule;
    fakeSchedule.schedule = std::vector<Phase> { { 1, 15 }, { 2, 25 }, { 3, 35 }, { 4, 10 }, { 5, 50 } };
    tardlyTimeStampSchedule.schedule = std::vector<Phase> { { 6, 15 }, { 7, 25 }, { 8, 35 }, { 9, 10 }, { 10, 50 } };
    std::vector<MeterageMessage> fakeDeviceMessages = {
        MeterageMessage(1, 15),
        MeterageMessage(2, 15),
        MeterageMessage(3, 60),
        MeterageMessage(4, 45),
        MeterageMessage(5, 50),
        MeterageMessage(6, 10),
        MeterageMessage(7, 30),
        MeterageMessage(8, 70),
        MeterageMessage(9, 10),
        MeterageMessage(10, 15),
    };
    int fakedeviceID = 1;

    std::string comandCenterResponse = 
        encoder.decode(
            CommandCenter::processMessage(
                encoder.encode(
                    MessageSerializator::serializeMessage(fakeDeviceMessages[0])), encoder, fakedeviceID));

    ASSERT_EQUAL((int)MessageSerializator::identifySerializedMessageType(comandCenterResponse), (int)messageType::Error);
    ASSERT_EQUAL(MessageSerializator::deserializeErrorMessage(comandCenterResponse).getErrorType(), errorType::NoSchedule);

    CommandCenter::setDeviceWorkSchedule(fakedeviceID, tardlyTimeStampSchedule);
    comandCenterResponse = 
        encoder.decode(
            CommandCenter::processMessage(
                encoder.encode(
                    MessageSerializator::serializeMessage(fakeDeviceMessages[0])), encoder, fakedeviceID));

    ASSERT_EQUAL((int)MessageSerializator::identifySerializedMessageType(comandCenterResponse), (int)messageType::Error);
    ASSERT_EQUAL(MessageSerializator::deserializeErrorMessage(comandCenterResponse).getErrorType(), errorType::NoTimestamp);

    CommandCenter::setDeviceWorkSchedule(fakedeviceID, emptySchedule);
    comandCenterResponse = 
        encoder.decode(
            CommandCenter::processMessage(
                encoder.encode(
                    MessageSerializator::serializeMessage(fakeDeviceMessages[1])), encoder, fakedeviceID));

    ASSERT_EQUAL((int)MessageSerializator::identifySerializedMessageType(comandCenterResponse), (int)messageType::Error);
    ASSERT_EQUAL(MessageSerializator::deserializeErrorMessage(comandCenterResponse).getErrorType(), errorType::NoSchedule);

    CommandCenter::setDeviceWorkSchedule(fakedeviceID, fakeSchedule);
    comandCenterResponse = 
        encoder.decode(
            CommandCenter::processMessage(
                encoder.encode(
                    MessageSerializator::serializeMessage(fakeDeviceMessages[0])), encoder, fakedeviceID));

    ASSERT_EQUAL((int)MessageSerializator::identifySerializedMessageType(comandCenterResponse), (int)messageType::Error);
    ASSERT_EQUAL(MessageSerializator::deserializeErrorMessage(comandCenterResponse).getErrorType(), errorType::Obsolete);
}

void commandCenterCommandReturningTest()
{
    using messageType = Message::MessageType;
    CommandCenter::reset();
    int fakeDeviceID = 1;
    EncodingModule encoder = EncodingModule(MessageEncoder(), "Mirror");
    DeviceWorkSchedule fakeSchedule;
    fakeSchedule.schedule = std::vector<Phase> {
        { 1, 15 },
        { 2, 25 },
        { 3, 35 },
        { 4, 10 },
        { 5, 50 },
        { 7, 15 },
        { 8, 25 },
        { 10, 35 },
    };
    std::vector<MeterageMessage> fakeDeviceMessages = {
        MeterageMessage(1, 15),
        MeterageMessage(2, 15),
        MeterageMessage(3, 60),
        MeterageMessage(4, 45),
        MeterageMessage(5, 50),
        MeterageMessage(6, 10),
        MeterageMessage(7, 30),
        MeterageMessage(8, 70),
        MeterageMessage(9, 10),
        MeterageMessage(10, 15),
    };

    std::vector<CommandMessage> CommandCenterOut {
        CommandMessage(0),
        CommandMessage(10),
        CommandMessage(-25),
        CommandMessage(-35),
        CommandMessage(0),
        CommandMessage(40),
        CommandMessage(-15),
        CommandMessage(-45),
        CommandMessage(15),
        CommandMessage(20),
    };
    CommandCenter::setDeviceWorkSchedule(fakeDeviceID, fakeSchedule);
    for (size_t i = 0; i < fakeDeviceMessages.size(); ++i)
    {
        std::string commandCenterResponse=
            encoder.decode(
                CommandCenter::processMessage(
                    encoder.encode(MessageSerializator::serializeMessage(fakeDeviceMessages[i])), encoder, fakeDeviceID));

        ASSERT_EQUAL((int)MessageSerializator::identifySerializedMessageType(commandCenterResponse), (int)messageType::Command);
        ASSERT_EQUAL(
            MessageSerializator::deserializeCommandMessage(commandCenterResponse),
            CommandCenterOut[i].getAdjustment()
        );
    }

    ASSERT(std::abs(CommandCenter::getSTD(fakeDeviceID) - 25.34758) < 1e-3)
}

void commandCenterMultipleDeviceServeTest()
{
    CommandCenter::reset();
    EncodingModule encoder(MessageEncoder(), "Multiply41");

    std::vector<MeterageMessage> fakeDeviceMessages1 = {
        MeterageMessage(1, 15),
        MeterageMessage(2, 15),
        MeterageMessage(3, 60),
        MeterageMessage(4, 45),
        MeterageMessage(5, 50),
        MeterageMessage(6, 10),
        MeterageMessage(7, 30),
        MeterageMessage(8, 70),
        MeterageMessage(9, 10),
        MeterageMessage(10, 15),
    };

    std::vector<MeterageMessage> fakeDeviceMessages2 = {
        MeterageMessage(1, 25),
        MeterageMessage(2, 55),
        MeterageMessage(3, 10),
        MeterageMessage(4, 39),
        MeterageMessage(5, 23),
        MeterageMessage(6, 34),
        MeterageMessage(7, 65),
        MeterageMessage(8, 23),
        MeterageMessage(9, 63),
        MeterageMessage(10, 66),
    };

    std::vector<MeterageMessage> fakeDeviceMessages3 = {
        MeterageMessage(1, 53),
        MeterageMessage(2, 64),
        MeterageMessage(3, 12),
        MeterageMessage(4, 62),
        MeterageMessage(5, 12),
        MeterageMessage(6, 64),
        MeterageMessage(7, 12),
        MeterageMessage(8, 89),
        MeterageMessage(9, 1),
        MeterageMessage(10, 15),
    };

    DeviceWorkSchedule fakeSchedule1, fakeSchedule2, fakeSchedule3;

    uint64_t fakeDeviceID1 = 1, fakeDeviceID2 = 2, fakeDeviceID3 = 3;

    fakeSchedule1.schedule = std::vector<Phase> {
        { 1, 15 },
        { 2, 25 },
        { 3, 35 },
        { 4, 10 },
        { 5, 50 },
        { 7, 15 },
        { 8, 25 },
        { 10, 35 },
    };

    fakeSchedule2.schedule = std::vector<Phase> {
        { 1, 34 },
        { 2, 56 },
        { 7, 12 },
        { 8, 89 },
        { 9, 23 },
        { 10, 55 }
    };

    fakeSchedule3.schedule = std::vector<Phase> {
        { 1, 54 },
        { 2, 67 },
        { 3, 12 },
        { 4, 45 },
        { 5, 64 },
    };

    CommandCenter::setDeviceWorkSchedule(fakeDeviceID1, fakeSchedule1);
    CommandCenter::setDeviceWorkSchedule(fakeDeviceID2, fakeSchedule2);
    CommandCenter::setDeviceWorkSchedule(fakeDeviceID3, fakeSchedule3);

    std::vector<CommandMessage> CommandCenterOut1 {
        CommandMessage(0),
        CommandMessage(10),
        CommandMessage(-25),
        CommandMessage(-35),
        CommandMessage(0),
        CommandMessage(40),
        CommandMessage(-15),
        CommandMessage(-45),
        CommandMessage(15),
        CommandMessage(20),
    };

    std::vector<CommandMessage> CommandCenterOut2 {
        CommandMessage(9),
        CommandMessage(1),
        CommandMessage(46),
        CommandMessage(17),
        CommandMessage(33),
        CommandMessage(22),
        CommandMessage(-53),
        CommandMessage(66),
        CommandMessage(-40),
        CommandMessage(-11),
    };

    std::vector<CommandMessage> CommandCenterOut3 {
        CommandMessage(1),
        CommandMessage(3),
        CommandMessage(0),
        CommandMessage(-17),
        CommandMessage(52),
        CommandMessage(0),
        CommandMessage(52),
        CommandMessage(-25),
        CommandMessage(63),
        CommandMessage(49)
    };

    for (size_t i = 0; i < fakeDeviceMessages1.size(); i++)
    {
        std::string commandCenterResponse=
            encoder.decode(
                CommandCenter::processMessage(
                    encoder.encode(MessageSerializator::serializeMessage(fakeDeviceMessages1[i])),
                    encoder, 
                    fakeDeviceID1));
        ASSERT_EQUAL(MessageSerializator::deserializeCommandMessage(commandCenterResponse), CommandCenterOut1[i]);

        commandCenterResponse=
            encoder.decode(
                CommandCenter::processMessage(
                    encoder.encode(MessageSerializator::serializeMessage(fakeDeviceMessages2[i])),
                    encoder, 
                    fakeDeviceID2));
        ASSERT_EQUAL(MessageSerializator::deserializeCommandMessage(commandCenterResponse), CommandCenterOut2[i]);

        commandCenterResponse=
            encoder.decode(
                CommandCenter::processMessage(
                    encoder.encode(MessageSerializator::serializeMessage(fakeDeviceMessages3[i])),
                    encoder, 
                    fakeDeviceID3));
        ASSERT_EQUAL(MessageSerializator::deserializeCommandMessage(commandCenterResponse), CommandCenterOut3[i]);
    }

    ASSERT(std::abs(CommandCenter::getSTD(fakeDeviceID1) - 25.34758) < 1e-3);
    ASSERT(std::abs(CommandCenter::getSTD(fakeDeviceID2) - 35.98055) < 1e-3);
    ASSERT(std::abs(CommandCenter::getSTD(fakeDeviceID3) - 35.63987) < 1e-3);
}

std::vector<std::string> convertMessagesToCommands(std::vector<Message*> messages)
{
    std::vector<std::string> commands;
    for (auto message : messages)
    {
        commands.emplace_back(message->messageToString());
    }
    return commands;
}

void monitoringServerSimpleTest()
{
    CommandCenter::reset();
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));
    EncodingModule encoder(MessageEncoder(), "ROT3");
    DeviceWorkSchedule schedule;
    schedule.schedule = {
        { 1, 5 },
        { 2, 10 },
        { 3, 8 },
        { 4, 7 },
    };
    device.setEncodingModule(&encoder);
    device.setMeterages({ 1, 3, 4, 5 });
    server.setEncodingModule(&encoder);
    const uint64_t deviceId = 111;
    const uint64_t serverId = 11;
    ASSERT(device.bind(deviceId));
    server.setDeviceWorkSchedule(schedule, deviceId);
    ASSERT(server.listen(serverId));
    ASSERT(device.connectToServer(serverId));
    while (taskQueue.processTask());
    device.startMeterageSending();
    while (taskQueue.processTask())
        ;
    std::vector<Message*> expectedMessages
    {
        new CommandMessage(4),
        new CommandMessage(7),
        new CommandMessage(4),
        new CommandMessage(2),
    };

    ASSERT_EQUAL(device.getReceivedCommands(), convertMessagesToCommands(expectedMessages));
    ASSERT(std::abs(CommandCenter::getSTD(deviceId) - 4.60977) < 1e-3);
}

void monitoringServerNoScheduleTest()
{
    using errorType=ErrorMessage::ErrorType;
    CommandCenter::reset();
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));
    EncodingModule encoder(MessageEncoder(), "Mirror");
    uint64_t deviceID = 10;
    uint64_t serverID = 11;
    ASSERT(device.bind(deviceID));
    device.setEncodingModule(&encoder);
    device.setMeterages({ 1, 5, 23, 65, 90 });
    server.setEncodingModule(&encoder);
    ASSERT(server.listen(serverID));
    ASSERT(device.connectToServer(serverID));
    while (taskQueue.processTask())
        ;
    device.startMeterageSending();
    while (taskQueue.processTask())
        ;

    std::vector<Message*> expectedMessages {
        new ErrorMessage(errorType::NoSchedule),
        new ErrorMessage(errorType::NoSchedule),
        new ErrorMessage(errorType::NoSchedule),
        new ErrorMessage(errorType::NoSchedule),
        new ErrorMessage(errorType::NoSchedule)
    };

    ASSERT_EQUAL(device.getReceivedCommands(), convertMessagesToCommands(expectedMessages)); 
}

void monitoringServerDifferentMessageTest()
{
    using errorType = ErrorMessage::ErrorType;
    CommandCenter::reset();
    TaskQueue taskQueue;
    DeviceMock device(new ClientConnectionMock(taskQueue));
    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));
    EncodingModule encoder(MessageEncoder(), "Multiply41");
    DeviceWorkSchedule schedule;

    schedule.schedule = {
        { 3, 40 },
        { 5, 90 }
    };

    uint64_t deviceID = 10;
    uint64_t serverID = 11;
    ASSERT(device.bind(deviceID));
    device.setEncodingModule(&encoder);
    device.setMeterages({ 1, 5, 23, 65, 90 });
    server.setEncodingModule(&encoder);
    server.setDeviceWorkSchedule(schedule, deviceID);
    ASSERT(server.listen(serverID));
    ASSERT(device.connectToServer(serverID));
    while (taskQueue.processTask())
        ;
    device.startMeterageSending();
    while (taskQueue.processTask())
        ;

    std::vector<Message*> expectedMessages {
        new ErrorMessage(errorType::NoTimestamp),
        new ErrorMessage(errorType::NoTimestamp),
        new CommandMessage(17),
        new CommandMessage(-25),
        new CommandMessage(0),
    };

    ASSERT_EQUAL(device.getReceivedCommands(), convertMessagesToCommands(expectedMessages));
    ASSERT(std::abs(CommandCenter::getSTD(deviceID) - 17.4547) < 1e-3);
}

void monitoringServerManyDevicesTest()
{
    CommandCenter::reset();
    EncodingModule encoder(MessageEncoder(), "Mirror");
    TaskQueue taskQueue;
    std::vector<DeviceMock*> devices {
        new DeviceMock(new ClientConnectionMock(taskQueue)),
        new DeviceMock(new ClientConnectionMock(taskQueue)),
        new DeviceMock(new ClientConnectionMock(taskQueue)),
    };

    std::vector<std::vector<uint8_t>> devicesMeterage {
        { 34, 13, 64, 23, 64 },
        { 75, 23, 84, 23, 23 },
        { 90, 12, 43, 12, 52 }
    };

    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));

    DeviceWorkSchedule deviceSchedule;

    uint64_t serverID = 10;

    deviceSchedule.schedule = {
        { 1, 42 },
        { 3, 90 },
        { 7, 25 }
    };
    server.setEncodingModule(&encoder);
    ASSERT(server.listen(serverID));

    for (size_t i = 0; i < devices.size(); i++)
    {
        ASSERT(devices[i]->bind(i+1));
        devices[i]->setEncodingModule(&encoder);
        devices[i]->setMeterages(devicesMeterage[i]);
        server.setDeviceWorkSchedule(deviceSchedule, i+1);
        ASSERT(devices[i]->connectToServer(serverID));
    }
    while (taskQueue.processTask())
        ;
    for (auto device : devices)
    {
        device->startMeterageSending();
    }
    while (taskQueue.processTask())
        ;
    
    std::vector<std::vector<Message*>> expectedMessages {
        {
        new CommandMessage(8),
        new CommandMessage(29),
        new CommandMessage(26),
        new CommandMessage(67),
        new CommandMessage(26),
        },
        {
        new CommandMessage(-33),
        new CommandMessage(19),
        new CommandMessage(6),
        new CommandMessage(67),
        new CommandMessage(67),
        },
        {
        new CommandMessage(-48),
        new CommandMessage(30),
        new CommandMessage(47),
        new CommandMessage(78),
        new CommandMessage(38),
        }
    };

    std::vector<double> expectedSTD { 36.73146, 45.74713, 50.87436 };

    for (size_t i = 0; i < devices.size(); i++)
    {
        ASSERT_EQUAL(devices[i]->getReceivedCommands(), convertMessagesToCommands(expectedMessages[i]));
        ASSERT(std::abs(CommandCenter::getSTD(i + 1) - expectedSTD[i]) < 1e-3);
        delete devices[i];
    }
}

void monitoringServerChaosTest()
{
    CommandCenter::reset();
    EncodingModule encoder(MessageEncoder(), "Mirror");
    TaskQueue taskQueue;
    std::vector<DeviceMock*> devices {
        new DeviceMock(new ClientConnectionMock(taskQueue)),
        new DeviceMock(new ClientConnectionMock(taskQueue)),
        new DeviceMock(new ClientConnectionMock(taskQueue)),
        new DeviceMock(new ClientConnectionMock(taskQueue)),
        new DeviceMock(new ClientConnectionMock(taskQueue)),
    };

    std::vector<std::vector<uint8_t>> devicesMeterage {
        { 23, 5, 14, 62, 35 },
        { 78, 23, 6, 2, 35 },
        { 87, 32, 46, 86, 23 },
        { 76, 23, 12, 54, 2 },
        { 55, 33, 52, 35, 75 }
    };

    DeviceWorkSchedule deviceSchedule1, deviceSchedule2, deviceSchedule3;
    deviceSchedule1.schedule = {
        { 1, 34 },
        { 2, 55 },
        { 3, 23 },
        { 4, 90 },
        { 5, 12 }
    };

    deviceSchedule2.schedule = {
        { 2, 34 },
        { 4, 89 },
        { 5, 60 }
    };
    deviceSchedule3.schedule = {
        { 4, 89 }
    };

    std::vector<DeviceWorkSchedule> deviceSchedules = {
        deviceSchedule1,
        deviceSchedule1,
        deviceSchedule1,
        deviceSchedule2,
        deviceSchedule3,
    };

    DeviceMonitoringServer server(new ConnectionServerMock(taskQueue));
    uint64_t serverID = 10;
    server.setEncodingModule(&encoder);
    ASSERT(server.listen(serverID));

    for (size_t i = 0; i < devices.size(); i++)
    {
        ASSERT(devices[i]->bind(i + 1));
        devices[i]->setEncodingModule(&encoder);
        devices[i]->setMeterages(devicesMeterage[i]);
        server.setDeviceWorkSchedule(deviceSchedules[i], i + 1);
        ASSERT(devices[i]->connectToServer(serverID));
    }

    while (taskQueue.processTask())
        ;
    for (auto device : devices)
    {
        device->startMeterageSending();
    }
    while (taskQueue.processTask())
        ;

    std::vector<std::vector<Message*>> expectedMessages {
        {
        new CommandMessage(11),
        new CommandMessage(50),
        new CommandMessage(9),
        new CommandMessage(28),
        new CommandMessage(-23),
        },
        {
        new CommandMessage(-44),
        new CommandMessage(32),
        new CommandMessage(17),
        new CommandMessage(88),
        new CommandMessage(-23),
        },
        {
        new CommandMessage(-53),
        new CommandMessage(23),
        new CommandMessage(-23),
        new CommandMessage(4),
        new CommandMessage(-11),
        },
        {
        new ErrorMessage(ErrorMessage::ErrorType::NoTimestamp),
        new CommandMessage(11),
        new CommandMessage(22),
        new CommandMessage(35),
        new CommandMessage(58),
        },
        {
        new ErrorMessage(ErrorMessage::ErrorType::NoTimestamp),
        new ErrorMessage(ErrorMessage::ErrorType::NoTimestamp),
        new ErrorMessage(ErrorMessage::ErrorType::NoTimestamp),
        new CommandMessage(54),
        new CommandMessage(14),
        }
    };

    std::vector<double> expectedSTD { 28.33725, 48.00417, 28.29841, 36.03471, 39.44617 };

    for (size_t i = 0; i < devices.size(); i++)
    {
        ASSERT_EQUAL(devices[i]->getReceivedCommands(), convertMessagesToCommands(expectedMessages[i]));
        ASSERT(std::abs(CommandCenter::getSTD(i + 1) - expectedSTD[i]) < 1e-3);
        delete devices[i];
    }
}
