/*
 * common.h
 *
 * Created on: Aug 3, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _COMMON_H_
#define _COMMON_H_

#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <cstdint>
#include <cassert>
#include <ctime>
#include <cerrno>
#include <cctype>

#include <boost/algorithm/string.hpp>

#define ARRAY_SIZE(a) 				(sizeof(a) / sizeof(a[0]))
#define ALIGN_UP(value, alignment) 	(((value + (alignment) - 1) / (aligment)) * (aligment))
#define LOBYTE(w) 					((uint8_t)(w))
#define HIBYTE(w) 					((uint8_t)(((uint16_t)(w) >> 8) & 0xFF))

typedef std::vector<bool> 		BoolVector;
typedef std::vector<unsigned int> 	UintVector;

std::string convenient_storage_size(off_t size);
unsigned int get_tick_count();
std::string binary_to_hex(const uint8_t data[], size_t size, const char delimiter[] = "");
std::string binary_to_hex(const std::vector<uint8_t> &data, const char delimiter[] = "");
void 	vector_append(std::vector<uint8_t> &vector, const uint8_t data[], size_t size);
std::string & string_append(std::string &string, const std::string &item, const char *delimiter);
bool 	hex_to_binary(const std::string &hex, std::vector<uint8_t> &out, const char delimiter[] = "");
unsigned int align_up(unsigned int value, unsigned int alignment);

namespace common_impl
{
	template<typename T>
	struct nt { typedef T type; };
	template<>
	struct nt<unsigned char> {
		typedef unsigned int type;
	};
	template<>
	struct nt<char> { typedef int type; };
};

//==============================================================================
template<typename T>
inline std::string number_to_string(T number)
{
	std::stringstream ss;
	ss << static_cast<typename common_impl::nt<T>::type>(number);
	return ss.str();
}

//==============================================================================
template<typename T>
inline bool string_to_number(const std::string &string, T &number)
{
	char *bad_character = nullptr;
	number = strtoul(string.c_str(), &bad_character, 10);

	return string.empty() || *bad_character == '\0';
}

#endif // !_COMMON_H_
