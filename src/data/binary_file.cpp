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
#include <fstream>
#include <system_error>

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
void binary_file_load(const fs::path &path, std::vector<uint8_t> &vector)
{
	auto resolved_path = resolve_path(path);
	std::error_code error;
	auto size = fs::file_size(resolved_path, error);
	if (error) {
		throw FileException("Cannot get file size for " + resolved_path.string() + ": " + error.message());
	}

	auto file = std::ifstream(resolved_path, std::ios::binary);
	if (!file.good()) {
		file_io_error("Unable to open file", resolved_path);
	}
	vector.resize(size, 0U);
	file.read(reinterpret_cast<char *>(vector.data()), size);
	if (!file.good()) {
		file_io_error("Unable to read data from", resolved_path);
	}
}

//==============================================================================
void binary_file_save(const fs::path &path, const std::vector<uint8_t> &vector)
{
	auto resolved_path = resolve_path(path);
	auto file = std::ofstream(resolved_path, std::ios::binary | std::ios::trunc);
	if (!file.good()) {
		file_io_error("Unable to open file", resolved_path);
	}
	file.write(reinterpret_cast<const char *>(vector.data()), vector.size());
	if (!file.good()) {
		file_io_error("Unable to write data to", resolved_path);
	}
}
