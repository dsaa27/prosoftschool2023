#ifndef TESTS_H
#define TESTS_H

// TODO: собственные тесты
/*!
 * \brief Тест сервера.
 */
void monitoringServerTest1();

/*!
 * \brief Тест существующих шифровщиков и их переключения.
 */
void EncoderTest();

/*!
 * \brief Тест добавления шифровщика и переключения на него.
 */
void addEncoderTest();

/*!
 * \brief Тест преобразования с строку и обратно.
 */
void serialiserTest();

/*!
 * \brief Тест подключения нескольких устройств.
 */
void severalDeviceTest();

/*!
 * \brief Тест всех .
 */
void servAnswerTest();

#endif // TESTS_H
