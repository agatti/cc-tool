/*
 * log.h
 *
 * Created on: Nov 9, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _LOG_H_
#define _LOG_H_

#include <cstdio>
#include <cstdlib>
#include "common.h"

class Log
{
public:
	enum LogLevel { LL_INFO };

	void add(LogLevel level, const std::string &message, va_list ap);
	void set_log_file(const std::string &file_name);

	Log();
	~Log();
private:
	FILE *file_;
};

void log_info(const std::string &message, ...);
Log &log_get();

#endif // !_LOG_H_
