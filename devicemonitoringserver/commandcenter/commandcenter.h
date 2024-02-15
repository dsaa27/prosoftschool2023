#ifndef COMMANDCENTER_H
#define COMMANDCENTER_H

#include "../deviceworkschedule.h"
#include "../message/messages.h"
#include "../cryptographer/encoder/encoder.h"
#include "../serializer/serializer.h"
#include <numeric>

#include <vector>
#include <map>

class CommandCenter final
{
private:
    struct PhaseInfo
    {
        std::vector<Phase> phases;
        uint64_t currentTimestamp = 0;
        uint64_t currentIndex = 0;
        std::vector<uint16_t> stdDeviation;
    };
    struct DeviceInfo
    {
        DeviceWorkSchedule workSchedule;
        PhaseInfo phaseInfo;

        // Information about the selected crypt alg for the device is stored in the command center
        // CryptAlg for the device and for the command center may not match
        Encoder crypter;
    };

public:
    AbstractMessage* catchMessageFromDevice(uint64_t deviceId, const std::string msgDevice_str);
    bool setSchedule(const DeviceWorkSchedule& schedule);
    bool addDevice(const DeviceWorkSchedule& schedule);
    bool removeDevice(uint64_t deviceId);
    DeviceInfo getDeviceInfo(uint64_t deviceId);
    float getStdDevation(uint64_t deviceId);

private:
    std::map<uint64_t, DeviceInfo> m_devices;
    Serializer m_serializer;
};

#endif /* COMMANDCENTER */