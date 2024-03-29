/*
 * read_target.h
 *
 * Created on: Oct 31, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _READ_TARGET_H_
#define _READ_TARGET_H_

#include "common.h"

struct OptionFileInfo
{
	std::string type;
	std::string name;
	size_t offset;
};

void option_extract_file_info(const std::string &input, OptionFileInfo &file_info,
							  bool support_offset);

class ReadTarget
{
public:
	enum SourceType { ST_CONSOLE, ST_FILE };

	[[nodiscard]] SourceType source_type() const;
	void set_source(const std::string &input);
	void on_read(const std::vector<uint8_t> &data) const;

	ReadTarget();

private:
	std::string file_format_;
	std::string file_name_;
	SourceType source_type_;
};

#endif // !_READ_TARGET_H_
