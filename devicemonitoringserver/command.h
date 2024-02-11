#ifndef COMMAND_H
#define COMMAND_H
#include <stdint.h>
#include "abstractmessage.h"

struct Command: AbstractMessage
{
public:
	Command (const int8_t& adjustment = 0): m_adjustment(adjustment){}

	std::string Serialize() const override final;
	void Deserialize(std::istringstream&) override final;

	void SetAdjustment(const int8_t&);

	int8_t GetAdjustment() const;

private:
	int8_t m_adjustment;
};

typedef std::shared_ptr<Command> pCommand;

#endif // COMMAND_H
