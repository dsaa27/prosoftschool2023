#include "messagemeterage.h"

#include "bigendian.h"

void MessageMeterage::serialize(std::ostream& os) const
{
    toBigEndian(os, timeStamp());
    toBigEndian(os, meterage());
}

std::optional<MessageMeterage> MessageMeterage::deserialize(std::istream& is)
{
    uint64_t timeStamp;
    uint8_t meterage;
    timeStamp = fromBigEndian<uint64_t>(is);
    meterage = fromBigEndian<uint8_t>(is);
    if (is.fail())
        return {};
    return MessageMeterage(timeStamp, meterage);
}
