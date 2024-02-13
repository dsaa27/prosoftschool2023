#ifndef TESTS_H
#define TESTS_H

// TODO: собственные тесты
/*!
 * \brief Тест сервера.
 */
void messageSerializatorSerializeTest();
void messageSerializatorDeserializeTest();
void monitoringServerCommandTest();
void monitoringServerNoScheduleTest();
void monitoringServerNoTimeStampTest();
void monitoringServerCommandTwoDevicesTest();
void messageEncoderEncodeROT3Test();
void messageEncoderDecodeROT3Test();
void ROT3Test();
#endif // TESTS_H
