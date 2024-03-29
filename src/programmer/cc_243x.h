/*
 * cc_243x.h
 *
 * Created on: Nov 9, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _CC_243X_H_
#define _CC_243X_H_

#include "cc_unit_driver.h"

class CC_243x : public CC_UnitDriver
{
public:
	void supported_units(std::list<Unit_ID> &units) override;
	void find_unit_info(UnitInfo &info) override;

	bool erase_check_completed() override;

	void mac_address_read(size_t index, std::vector<uint8_t> &mac_address) override;

	void flash_write(const DataSectionStore &sections) override;
	void flash_read_block(size_t offset, size_t size, std::vector<uint8_t> &data) override;

	bool flash_image_embed_mac_address(DataSectionStore &sections,
			const std::vector<uint8_t> &mac_address) override;

	void convert_lock_data(const std::vector<std::string> &qualifiers,
						   std::vector<uint8_t>& lock_data) override;

	bool config_write(const std::vector<uint8_t> &mac_address, const std::vector<uint8_t> &lock_data) override;

	CC_243x(USB_Device &programmer, ProgressWatcher &pw);
};

#endif // !_CC_243X_H_
