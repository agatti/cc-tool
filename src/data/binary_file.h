/*
 * binary_file.h
 *
 * Created on: Jul 30, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 *    License: GNU GPL v2
 */

#ifndef _BINARY_FILE_H_
#define _BINARY_FILE_H_

#include "common.h"

void binary_file_load(const std::string &file_name, std::vector<uint8_t> &vector);
void binary_file_save(const std::string &file_name, const std::vector<uint8_t> &vector);

#endif // !_BINARY_FILE_H_
