#ifndef BIGENDIAN_H
#define BIGENDIAN_H

#include <istream>
#include <ostream>
#include <type_traits>

/*!
 * \brief Функция сериализации целого числа \a value типа \a T в поток \a ostream в виде последовательности байтов в порядке Big Endian
 */
template <typename T>
void toBigEndian(std::ostream& ostream, T value)
{
    constexpr size_t bytes_num = sizeof(value);
    using unsigned_T = std::make_unsigned_t<T>;
    unsigned_T mask = 0xFF;
    mask <<= (bytes_num - 1) * 8;

    for (size_t i = bytes_num; i > 0; --i)
    {
        ostream.put((value & mask) >> ((i - 1) * 8));
        mask >>= 8;
    }
}

/*!
 * \brief Функция десериализации целого числа типа \a T из потока \a istream в виде последовательности байтов в порядке Big Endian
 */
template <typename T>
T fromBigEndian(std::istream& istream)
{
    T value = 0;
    using unsigned_T = std::make_unsigned_t<T>;

    for (size_t i = sizeof(value); i > 0; --i)
    {
        unsigned_T add_byte = istream.get();
        add_byte <<= (i - 1) * 8;
        value |= add_byte;
    }
    return value;
}

#endif // BIGENDIAN_H