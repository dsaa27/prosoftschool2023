#include "meterage.h"

std::string Meterage::Serialize() const
{
	std::ostringstream os;
	os << "metrage"
	   << " " << m_meterage
	   << " " << m_timeStamp
	   << std::endl;
	return os.str();
}

void Meterage::Deserialize(std::istringstream& is)
{
	uint8_t meterage;
	uint64_t timeStamp;
	is >> m_meterage >> m_timeStamp;
}

uint8_t Meterage::getMeterage() const
{
	return m_meterage;
}

uint64_t Meterage::getTimeStamp() const
{
	return m_timeStamp;
}

void Meterage::setMeterage(const uint8_t& meterage)
{
	m_meterage = meterage;
}

void Meterage::setTimeStamp(const uint64_t& timeStamp)
{
	m_timeStamp = timeStamp;
}


