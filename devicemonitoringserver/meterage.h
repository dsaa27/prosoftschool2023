#ifndef METERAGE_H
#define METERAGE_H
#include <stdint.h>

class meterage
{
public:
	meterage(uint8_t meterage, uint64_t timeStamp): m_meterage(meterage), m_timeStamp(timeStamp) {}

	const uint64_t getTimeStamp() noexcept
	{
		return m_timeStamp;
	}

	const uint8_t getMeterage() noexcept
	{
		return m_meterage;
	}

private:
	uint8_t m_meterage;
	uint64_t m_timeStamp;
};

#endif // METERAGE_H
