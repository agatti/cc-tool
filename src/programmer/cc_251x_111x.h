/*
 * cc_251x_111x.h
 *
 * Created on: Nov 9, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _CC_251X_111X_H_
#define _CC_251X_111X_H_

#include "cc_unit_driver.h"

class CC_251x_111x : public CC_UnitDriver
{
public:
	void supported_units(Unit_ID_List &units) override;
	void find_unit_info(UnitInfo &info) override;

	bool erase_check_completed() override;

	void flash_write(const DataSectionStore &sections) override;
	void flash_read_block(size_t offset, size_t size, std::vector<uint8_t> &data) override;

	bool config_write(const std::vector<uint8_t> &mac_address, const std::vector<uint8_t> &lock_data) override;

	void convert_lock_data(const std::vector<std::string> &qualifiers,
						   std::vector<uint8_t>& lock_data) override;

	CC_251x_111x(USB_Device &programmer, ProgressWatcher &pw);
};

#endif // !_CC_251X_111X_H_
