#include "encoderexecutor.h"
#include <sstream>

/*!
* \brief Реализация методов для кодирования/декодирования при помощи шифра Цезаря
*/
std::string ROT3::encode (const std::string& rawMsg)  {
    std::string msg;
    
    for(char c : rawMsg) {
        if (static_cast<int>(c) == 127)
            c = static_cast<char>(2);
        else if (static_cast<int>(c) == 126)
            c = static_cast<char>(1);
        else if (static_cast<int>(c) == 125)
            c = static_cast<char>(0);
        else
            c += 3;

        msg.push_back(c);
    }

    return msg;
}

std::string ROT3::decode (const std::string& codedMsg)  {
    std::string msg;

    for(char c : codedMsg) {
        if (static_cast<int>(c) == 0)
            c = static_cast<char>(125);
        else if (static_cast<int>(c) == 1)
            c = static_cast<char>(126);
        else if (static_cast<int>(c) == 2)
            c = static_cast<char>(127);
        else
            c -= 3;

        msg.push_back(c);
    }

    return msg;
}


/*!
* \brief Реализация методов для кодирования/декодирования при помощи шифра "Mirror"
*/

std::string Mirror::encode (const std::string& rawMsg)  {
    std::string msg;

    for (char c : rawMsg) {
        int num = static_cast<int>(c);

        if (num < 10) {
            continue;
        }else if (num < 100) {
            int units = num % 10;
            num = num / 10 + units * 10;

            if (num < 10) {
                msg.push_back('{');
            }
        } else {
            num -= 100;
            int units = num % 10;
            num = num / 10 + units * 10;
            msg.push_back('}');
        }
        c = static_cast<char>(num);
        msg.push_back(c);
    }

    return msg;
}

std::string Mirror::decode (const std::string& codedMsg)  {
    std::string msg;
    int num;

    for(auto it = codedMsg.begin(); it != codedMsg.end(); ++it) {

        if (*it == '{') {
            ++it;
            num = static_cast<int>(*it);
            int units = num % 10;
            num = num / 10 + units * 10;
        } else if (*it == '}') {
            ++it;
            num = static_cast<int>(*it);
            int units = num % 10;
            num = num / 10 + units * 10;
            num += 100;
        } else {
            num = static_cast<int>(*it);

            if (num < 10) {
                continue;
            } else {
                int units = num % 10;
                num = num / 10 + units * 10;
            }
        }

        msg.push_back(static_cast<char>(num));
    }

    return msg;
}


/*!
* \brief Реализация методов для кодирования/декодирования при помощи шифра "Multiply41"
*/

std::string Multiply41::encode (const std::string& rawMsg)  {
    std::string msg;
    std::ostringstream buf;
    int num, count = 0;
    bool first = true;

    for (char c : rawMsg) {
        num = static_cast<int>(c);
        num *= 41;
        buf << ' ' << num;
        ++count;
    }

    msg = buf.str();
    buf.str("");
    buf.clear();
    buf << count << msg;
    return buf.str();
}

std::string Multiply41::decode (const std::string& codedMsg)  {
    std::istringstream stream(codedMsg);
    int msgLen, num;
    std::string msg;

    stream >> msgLen;
    for (;msgLen-- > 0;) {
        stream >> num;
        num /= 41;
        msg.push_back(static_cast<char>(num));
    }

    return msg;
}


/*!
* \brief Реализация методов для кодирования/декодирования при помощи шифра "Multiply5"
* \brief Этот алгоритм нужен для тестов класса MessageEncoder
*/

std::string Multiply5::encode (const std::string& rawMsg)  {
    std::string msg;
    std::ostringstream buf;
    int num, count = 0;
    bool first = true;

    for (char c : rawMsg) {
        num = static_cast<int>(c);
        num *= 5;
        buf << ' ' << num;
        ++count;
    }

    msg = buf.str();
    buf.str("");
    buf.clear();
    buf << count << msg;
    return buf.str();
}

std::string Multiply5::decode (const std::string& codedMsg)  {
    std::istringstream stream(codedMsg);
    int msgLen, num;
    std::string msg;

    stream >> msgLen;
    for (;msgLen-- > 0;) {
        stream >> num;
        num /= 5;
        msg.push_back(static_cast<char>(num));
    }

    return msg;
}