/*
 * common.cpp
 *
 * Created on: Nov 11, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#include <sys/time.h>
#include "common.h"

//==============================================================================
uint_t align_up(uint_t value, uint_t alignment)
{
	return ((value + alignment - 1) / alignment) * alignment;
}

//==============================================================================
bool hex_to_binary(const String &hex, ByteVector &out, const char delimiter[])
{
	const char *str = hex.c_str();
	char buffer[3] = { 0, 0, 0 };

	while (*str)
	{
		while (*str && strchr(delimiter, *str) != nullptr) str++;
		if (!*str)
			break;

		buffer[0] = *str++;
		if (!*str)
			return false;
		buffer[1] = *str++;

		char *error = nullptr;
		out.push_back(std::strtoul(buffer, &error, 16));
		if (*error != '\0')
			return false;
	}
	return true;
}

//==============================================================================
String binary_to_hex(const uint8_t data[], size_t size, const char delimiter[])
{
	std::stringstream ss;
	ss << std::setfill('0') << std::hex << std::uppercase;

	while (size--)
	{
		ss << std::setw(2) << (int)*data++;
		if (size)
			 ss << delimiter;
	}
	return ss.str();
}

//==============================================================================
uint_t get_tick_count()
{
    struct timeval tv;

    gettimeofday(&tv, nullptr);
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

//==============================================================================
String convenient_storage_size(off_t size)
{
	const String measure[] = { " B", " KB", " MB", " GB" };

	size_t index = 0;
	while (size > 1024 && index < (ARRAY_SIZE(measure) - 1))
	{
		size = size / 1024;
		index++;
	}
	return number_to_string(size) + measure[index];
}

//==============================================================================
String binary_to_hex(const ByteVector &data, const char delimiter[])
{	return binary_to_hex(&data[0], data.size(), delimiter); }

//==============================================================================
void vector_append(ByteVector &vector, const uint8_t data[], size_t size)
{	vector.insert(vector.end(), data, data + size); }

//==============================================================================
String &string_append(String &string, const String &item, const char *delimiter)
{
	if (!string.empty())
		string.append(delimiter);

	return string;
}
