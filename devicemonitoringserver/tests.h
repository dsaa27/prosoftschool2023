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

void serialiserTest();

/*!
 * \brief Тест добавления шифровщика и переключения на него.
 */
void addEncoderTest();

/*!
 * \brief Тест подключения нескольких устройств.
 */
void severalDeviceTest();

/*!
 * \brief Тест всех .
 */
void commandCenterTest();

#endif // TESTS_H
