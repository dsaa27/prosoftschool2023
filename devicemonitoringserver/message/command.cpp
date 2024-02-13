#include "command.h"

std::string Command::serialize() const
{
	std::ostringstream os;
	os << "command "
	   << m_adjustment;
	return os.str();
}

void Command::deserialize(std::istringstream& is)
{
	is >> m_adjustment;
}

int8_t Command::getAdjustment() const
{
	return m_adjustment;
}

bool Command::operator==(const Command& command)
{
	return this->getAdjustment() == command.getAdjustment();
}


