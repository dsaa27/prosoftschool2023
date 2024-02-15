#include "mirror.h"

#include <limits>

/*Three-digit characters are encoded in a special way:
* digits are encoded negative (123 -> -123) with the third digit discarded (-123 -> -23),
* followed by mirroring (-23 -> -32)*/

/* This approach is associated with the ambiguity of the cipher in the case of three-digit numbers, for example
* 123 -> [ENCODE] -> 321 -> [TO_CHAR, limit 128] -> 65 -> [DECODE] -> 56
* In turn, the technical specification does not describe how 3-digit characters should behave
*/ 

// 100 -> -100 ! Because '\0' symb in messages other than line termination is not allowed.

std::string MirrorCrypt::encode(const std::string& message) const
{
    std::string encodeMessage(message);
    for (auto& c : encodeMessage)
    {
        int c1;
        int c2;
        char c_temp = c;
        if (static_cast<int>(c) == 100)
        {
            c1 = 0;
            c2 = -100;
        }
        else if (static_cast<int>(c) > 100)
        {
            c_temp %= 100;
            c1 = - static_cast<int>(c_temp) % 10;
            c2 = - static_cast<int>(c_temp) / 10;
        }
        else
        {
            c1 = static_cast<int>(c_temp) % 10;
            c2 = static_cast<int>(c_temp) / 10;
        }
        c = c1 * 10 + c2;
    }
    return encodeMessage;
}

std::string MirrorCrypt::decode(const std::string& message) const
{
    std::string decodeMessage(message);
    for (auto& c : decodeMessage)
    {
        char c_temp = c;
        char c1;
        char c2;
        if (c_temp == -100)
        {
            c = 100;
        }
        else if (c_temp < 0)
        {
            c_temp *= -1;
            c1 = static_cast<int>(c_temp) % 10;
            c2 = static_cast<int>(c_temp) / 10;
            c_temp = c1 * 10 + c2;
            c_temp += 100;
            c = c_temp;
        }
        else
        {
            c1 = static_cast<int>(c_temp) % 10;
            c2 = static_cast<int>(c_temp) / 10;
            c_temp = c1 * 10 + c2;
            c = c_temp;
        }
    }
    return decodeMessage;
}