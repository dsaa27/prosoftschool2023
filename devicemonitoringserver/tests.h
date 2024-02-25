#ifndef TESTS_H
#define TESTS_H

// TODO: собственные тесты
/*!
 * \brief Тест сервера.
 */
void deviceIdBindingTest();
void messageEqualOperatorTest();
void messageSerializatorSerializeTest();
void messageSerializatorDeserializeTest();
void messageSerializatorInverseSerializatorTest();
void messageEncoderROT3Test();
void messageEncoderMirrorTest();
void messageEncoderMultiply41Test();
void messageEncoderMultyEncodingTest();
void messageEncoderCustomAlgorithmTest();
void commandCenterErrorReturningTest();
void commandCenterCommandReturningTest();
void commandCenterMultipleDeviceServeTest();
void monitoringServerSimpleTest();
void monitoringServerNoScheduleTest();
void monitoringServerDifferentMessageTest();
void monitoringServerManyDevicesTest();
void monitoringServerChaosTest();
;

#endif // TESTS_H
