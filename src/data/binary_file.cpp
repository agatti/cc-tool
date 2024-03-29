/*
 * binary_file.cpp
 *
 * Created on: Jul 30, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#include <filesystem>
#include <cstdio>
#include <system_error>

#include "binary_file.h"
#include "file.h"

namespace fs = std::filesystem;

//==============================================================================
void file_io_error(const std::string &message, const std::string &file_name)
{
    std::string error = message + " " + file_name + ": " + strerror(errno);

	throw FileException(error);
}

static const fs::path& resolve_path(const fs::path &path) {
	std::error_code error;
	auto status = fs::status(path, error);

	if (error) {
		throw FileException("Cannot get file status for " + path.string() + ": " + error.message());
	}

	if (status.type() == fs::file_type::directory) {
		throw FileException(path.string() + " is a directory.");
	}

	if (status.type() == fs::file_type::not_found) {
		throw FileException(path.string() + " was not found.");
	}

	if (status.type() == fs::file_type::unknown) {
		throw FileException(path.string() + " is of an unknown type.");
	}

	if (status.type() == fs::file_type::symlink) {
		auto resolved = fs::read_symlink(path, error);
		if (error) {
			throw FileException("Cannot resolve symlink " + path.string() + ": " + error.message());
		}
		return resolve_path(resolved);
	}

	return path;
}

//==============================================================================
void binary_file_load(const fs::path &file_name, std::vector<uint8_t> &vector)
{
	auto resolved_path = resolve_path(file_name);
	std::error_code error;
	auto size = fs::file_size(resolved_path, error);
	if (error) {
		throw FileException("Cannot get file size for " + resolved_path.string() + ": " + error.message());
	}

	FILE *file = fopen(resolved_path.c_str(), "r");
	if (!file)
		file_io_error("Unable to open file file", resolved_path);

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
void binary_file_save(const std::filesystem::path &file_name, const std::vector<uint8_t> &vector)
{
	auto resolved_path = resolve_path(file_name);

	FILE *file = fopen(resolved_path.c_str(), "w");
	if (!file)
		file_io_error("Unable to open file file", resolved_path);

	if (fwrite(&vector[0], 1, vector.size(), file) != vector.size() &&
			ferror(file) != 0)
	{
		fclose(file);
		file_io_error("Unable to write file", resolved_path);
		return;
	}

	if (fclose(file))
		file_io_error("Unable to close file", resolved_path);
}
