#include "messagecommand.h"

#include "bigendian.h"

#include <functional>
#include <optional>

void MessageCommand::serialize(std::ostream& os) const
{
    toBigEndian(os, command());
}

std::optional<MessageCommand> MessageCommand::deserialize(std::istream& is)
{
    int command;
    command = fromBigEndian<int8_t>(is);
    if (is.fail())
        return {};
    return MessageCommand(command);
}
