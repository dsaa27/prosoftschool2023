
#ifndef COMM_CENTER_H
#define COMM_CENTER_H

#include <map>
#include <vector>
#include <cstdint>
#include "../messages.h"
#include "../deviceworkschedule.h"



struct DeviceInfo {
    DeviceWorkSchedule devWorkSched;
    std::vector<Phase>  Phase_Log;        //log needed to compute rmsd 
    std::map<uint64_t, double> RMSD_log;  //time stamped log of rsmd's 
    uint64_t lastValidTime = 0;           
    uint64_t lastValidIndex = 0;           //last index in schedule that was in use 
};

class CommandCenter {

public:
    /*!
     * \brief Приём нового сообщения для обработки.
     * \param deviceId - идентификатор устройства
     * \param messageStruct - сообщение уже "разобранное" в структуру
     * \retval подготовленная структура сообщения-реакции
     */
    MessageBase acceptMessage(uint64_t deviceId, const MessageBase& messageStruct);

    /*!
     * \brief Регистрация нового устройства.
     * \param newDevSchedule - расписание работы устройства, содержаще его номер
     * \retval результат попытки (неудача если такое устр-во уже есть)
     */
    bool addDevice(const DeviceWorkSchedule& newDevSchedule);

    /*!
     * \brief Смена расписания работы устройсвта.
     * \param newDevSchedule - расписание работы устройства, содержаще его номер
     * \retval результат попытки 
     */
    bool changeSchedule(const DeviceWorkSchedule& newDevSchedule);

    /*!
     * \brief Удаление устройства.
     * \param deviceId - номер утсройства
     * \retval результат попытки (неудача если такого устройства)
     */
    bool removeDevice(uint64_t deviceId);

private:
    std::map<uint64_t, DeviceInfo*> mapOfDevices; 
    double getRMSD(uint64_t deviceId, uint8_t newValue);
};

#endif