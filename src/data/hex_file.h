/*
 * hex_file.h
 *
 * Created on: Jul 15, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _HEX_FILE_H_
#define _HEX_FILE_H_

#include <filesystem>

#include "data_section_store.h"

void hex_file_load(const std::filesystem::path &path, DataSectionStore &section_store, bool ignore_crc_mismatch = false);
void hex_file_save(const std::filesystem::path &path, const DataSectionStore &section_store);

#endif // !_HEX_FILE_H_
