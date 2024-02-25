#ifndef METERAGEMESSAGE_H
#define METERAGEMESSAGE_H
#include "message.h"
#include <utility>
class MeterageMessage final : public Message
{
public:
    MeterageMessage(uint64_t timeStamp, char meterage);
    ~MeterageMessage() override = default;
    std::string messageToString() const override;
    friend std::ostream& operator<<(std::ostream& out, const MeterageMessage& other);
    friend bool operator==(const MeterageMessage& meterage1, const MeterageMessage& meterage2);
    friend bool operator!=(const MeterageMessage& meterage1, const MeterageMessage& meterage2);
    std::pair<uint64_t, char> getMeterage() const;

private:
    std::pair<uint64_t, uint8_t> m_meterage;
};
#endif
