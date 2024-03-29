/*
 * data_section.h
 *
 * Created on: Jul 29, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _DATA_SECTION_H_
#define _DATA_SECTION_H_

#include <list>
#include "common.h"

struct DataSection
{
	[[nodiscard]] bool empty() const;
	[[nodiscard]] size_t size() const;
	[[nodiscard]] unsigned int next_address() const;

	DataSection();
	DataSection(unsigned int address, const std::vector<uint8_t> &data);
	DataSection(unsigned int address, const uint8_t data[], size_t size);

    unsigned int address;
	std::vector<uint8_t> data;
};

std::ostream& operator <<(std::ostream &os, const DataSection &o);

#endif // !_DATA_SECTION_H_
