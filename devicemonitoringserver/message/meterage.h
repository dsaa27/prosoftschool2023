#ifndef METERAGE_H
#define METERAGE_H
#include <stdint.h>
#include "abstractmessage.h"

class Meterage : public AbstractMessage
{
public:
	Meterage(const uint8_t& meterage = 0, const uint64_t& timeStamp = 0):
		m_meterage(meterage),
		m_timeStamp(timeStamp){}

	std::string Serialize() const override final;
	void Deserialize(std::istringstream&) override final;

	uint8_t getMeterage() const;
	uint64_t getTimeStamp() const;

private:
	uint8_t m_meterage;
	uint64_t m_timeStamp;
};

typedef std::shared_ptr<Meterage> pMeterage;

#endif // METERAGE_H
