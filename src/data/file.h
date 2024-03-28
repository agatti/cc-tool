/*
 * file.h
 *
 * Created on: Aug 1, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _FILE_H_
#define _FILE_H_

#include <stdexcept>

#include "common.h"

class FileException : public std::runtime_error
{
public:
	FileException(const String& arg) : std::runtime_error(arg) { }
};

#endif // !_FILE_H_
