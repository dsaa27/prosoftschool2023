#include "meterage.h"

std::string Meterage::serialize() const
{
	std::ostringstream os;
	os << "meterage"
	   << " " << m_meterage
	   << " " << m_timeStamp;
	return os.str();
}

void Meterage::deserialize(std::istringstream& is)
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

bool Meterage::operator ==(const Meterage& meterage)
{
	return (this->getMeterage() == meterage.getMeterage()) && (this->getTimeStamp() == meterage.getTimeStamp());

}
