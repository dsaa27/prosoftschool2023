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

void Command::SetAdjustment(const int8_t& adjustment)
{
	m_adjustment = adjustment;
}

int8_t Command::GetAdjustment() const
{
	return m_adjustment;
}


