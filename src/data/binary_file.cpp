/*
 * binary_file.cpp
 *
 * Created on: Jul 30, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#include <cstdio>
#include "binary_file.h"
#include "file.h"

//==============================================================================
void file_io_error(const std::string &message, const std::string &file_name)
{
    std::string error = message + " " + file_name + ": " + strerror(errno);

	throw FileException(error);
}

//==============================================================================
void binary_file_load(const std::string &file_name, ByteVector &vector)
{
	FILE *file = fopen(file_name.c_str(), "r");
	if (!file)
		file_io_error("Unable to open file file", file_name);

	fseek(file, 0, SEEK_END);
	size_t size = ftell(file);
	fseek(file, 0, SEEK_SET);

	vector.resize(size, 0);
	if (fread(&vector[0], 1, size, file) != size && ferror(file) != 0)
	{
		fclose(file);
		file_io_error("Unable to read file", file_name);
		return;
	}

	if (fclose(file))
		file_io_error("Unable to close file", file_name);
}

//==============================================================================
void binary_file_save(const std::string &file_name, const ByteVector &vector)
{
	FILE *file = fopen(file_name.c_str(), "w");
	if (!file)
		file_io_error("Unable to open file file", file_name);

	if (fwrite(&vector[0], 1, vector.size(), file) != vector.size() &&
			ferror(file) != 0)
	{
		fclose(file);
		file_io_error("Unable to write file", file_name);
		return;
	}

	if (fclose(file))
		file_io_error("Unable to close file", file_name);
}
