/*
 * data_section_store.h
 *
 * Created on: Jul 29, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _DATA_SECTION_STORE_H_
#define _DATA_SECTION_STORE_H_

#include "common.h"
#include "data_section.h"

/// Class store and manage a list of DataSections object in (ascending not-overlapped order)
class DataSectionStore
{
public:
	/// Return sum of all sections' sizes
	[[nodiscard]] size_t actual_size() const;

	/// Return the minor valid address
	[[nodiscard]] size_t lower_address() const;

	/// Return the address next to the most one
	[[nodiscard]] size_t upper_address() const;

	/// Add section to the store
	/// @return false if section overlapped and overwrite is false
	bool add_section(const DataSection &data, bool overwrite);

	/// Add all of DataSectionStore object's sections to the store
	/// @return false if section overlapped and overwrite is false
	bool add_sections(const DataSectionStore &section_store, bool overwrite);

	/// Remove all sections
	void remove_sections();

	/// Unite all sections to one continuoys memory block
	void create_image(uint8_t filler, std::vector<uint8_t> &image) const;

	[[nodiscard]] const std::list<DataSection> & sections() const;

private:
	std::list<DataSection> sections_;
};

#endif // !_DATA_SECTION_STORE_H_
