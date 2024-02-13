#include "command.h"

std::string Command::Serialize() const
{
	std::ostringstream os;
	os << "command "
	   << " " << m_adjustment
	   << std::endl;
	return os.str();
}

void Command::Deserialize(std::istringstream& is)
{
	is >> m_adjustment;
}

int8_t Command::GetAdjustment() const
{
	return m_adjustment;
}


