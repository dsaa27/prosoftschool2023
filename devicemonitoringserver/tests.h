#ifndef TESTS_H
#define TESTS_H

// TODO: собственные тесты
/*!
 * \brief Тест сервера - отправляем и получаем измерения
 */
void monitoringServerTest1();

/*!
 * \brief Тест существующих шифровщиков и их переключения.
 */
void EncoderTest();

/*!
 * \brief Тест переобразования в строку и обратно всех типов собщений
 */
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
 * \brief Тест обработки команд
 */
void commandCenterTest();

#endif // TESTS_H
