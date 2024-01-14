#ifndef BIGENDIAN_H
#define BIGENDIAN_H

#include <istream>
#include <ostream>

/*!
 * \brief Функция сериализации целого числа \a value типа \a T в поток \a ostream в виде последовательности байтов в порядке Big Endian
 */
template <typename T>
void toBigEndian(std::ostream& ostream, T value)
{
    constexpr size_t bytes_num = sizeof(value);
    unsigned char buf[bytes_num];
    for (size_t i = 0; i < bytes_num; ++i)
    {
        buf[i] = value;
        value >>= 8;
    }
    for (size_t i = bytes_num; i > 0; --i)
    {
        ostream.put(buf[i - 1]);
    }
}

/*!
 * \brief Функция десериализации целого числа типа \a T из потока \a istream в виде последовательности байтов в порядке Big Endian
 */
template <typename T>
T fromBigEndian(std::istream& istream)
{
    T value {};
    for (size_t i = 0; i < sizeof(T); ++i)
    {
        value <<= 8;
        value |= istream.get();
    }
    return value;
}

#endif // BIGENDIAN_H