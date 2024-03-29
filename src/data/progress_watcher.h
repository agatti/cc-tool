/*
 * progress_watcher.h
 *
 * Created on: Nov 12, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _PROGRESS_WATCHER_H_
#define _PROGRESS_WATCHER_H_

#include "common.h"
#include <boost/signals2.hpp>

class ProgressWatcher : boost::noncopyable
{
public:
	typedef boost::signals2::signal<void (unsigned int done_size, unsigned int full_size)> OnProgress;

	void do_on_read_progress(const OnProgress::slot_type &slot);
	void do_on_write_progress(const OnProgress::slot_type &slot);

	void read_progress(unsigned int done_chunk_size);
	void write_progress(unsigned int done_chunk_size);

	void read_start(size_t total_size);
	void read_finish();

	void write_start(size_t total_size);
	void write_finish();

	void enable(bool enable);

	ProgressWatcher();

private:
	unsigned int total_read_;
	unsigned int total_write_;
	bool read_started_;
	bool write_started_;
	unsigned int done_read_;
	unsigned int done_write_;
	bool enabled_;
	OnProgress on_read_progress_;
	OnProgress on_write_progress_;
};

#endif // !_PROGRESS_WATCHER_H_
