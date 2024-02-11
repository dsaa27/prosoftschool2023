#include "multiply41.h"
#include <limits>
const int charLimit = std::numeric_limits<char>::max() + 1;

std::string multiply41::Encode(const std::string& message) const
{
	std::string result;

	for (int symbol : message)
	{
		symbol *= 41;
		symbol = symbol % charLimit;
		result += symbol;
	}

	return result;
}

std::string multiply41::Decode(const std::string& encodedMessage) const
{
	std::string result;

	for (int symbol : encodedMessage)
	{
		symbol /= 41;
		symbol = (charLimit + symbol) % charLimit;
		result += symbol;
	}

	return result;
}

std::string multiply41::Name() const
{
	return name;
}
