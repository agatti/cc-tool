/*
 * cc_tool.cpp
 *
 * Created on: Aug 3, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _CC_FLASHER_H_
#define _CC_FLASHER_H_

#include <boost/program_options.hpp>
#include "data/binary_file.h"
#include "data/hex_file.h"
#include "data/read_target.h"
#include "data/data_section_store.h"
#include "programmer/cc_programmer.h"
#include "application/cc_base.h"

class CC_Flasher : public CC_Base
{
public:
	CC_Flasher();

private:
	void task_test();
	void task_erase();
	void task_read_flash();
	void task_write_flash();
	void task_verify_flash();
	void task_read_mac_address();
	void task_write_config();
	void task_read_info_page();

	bool validate_mac_options();
	bool validate_lock_options();
	bool validate_flash_size_options();

	void init_options(po::options_description &) override;
	bool read_options(const po::options_description &, const po::variables_map &) override;
	void process_tasks() override;

	std::string option_lock_data_;
	std::string option_info_page_;
	std::string option_verify_type_;
	std::string option_flash_size_;
	unsigned int task_set_;

	CC_Programmer::VerifyMethod verify_method_;
	DataSectionStore flash_write_data_;
	std::vector<uint8_t> mac_addr_;
	std::vector<uint8_t> lock_data_;

	ReadTarget flash_read_target_;
	ReadTarget info_page_read_target_;

	bool target_locked_;
};

#endif // !_CC_FLASHER_H_
