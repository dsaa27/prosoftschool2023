#include "rot3.h"
#include <limits>

const int charLimit = std::numeric_limits<char>::max() + 1;

std::string ROT3::encode(const std::string& message) const
{

	std::string result;

	for (int symbol : message)
	{
		symbol += 3;
		symbol = symbol % charLimit;
		result += symbol;
	}

	return result;
}

std::string ROT3::decode(const std::string& encodedMessage) const
{
	std::string result;

	for (int symbol : encodedMessage)
	{
		symbol -= 3;
		symbol = (charLimit + symbol) % charLimit;
		result += symbol;
	}

	return result;
}

std::string ROT3::getName() const
{
	return name;
}
