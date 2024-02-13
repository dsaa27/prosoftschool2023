#ifndef COMMAND_H
#define COMMAND_H
#include <stdint.h>
#include "abstractmessage.h"

class Command: public AbstractMessage
{
public:
	Command (const int8_t& adjustment = 0): m_adjustment(adjustment){}
	std::string serialize() const override final;
	void deserialize(std::istringstream&) override final;
	int8_t getAdjustment() const;

	bool operator==(const Command&);
private:
	int m_adjustment;
};

typedef std::shared_ptr<Command> pCommand;

#endif // COMMAND_H
