/*
 * cc_programmer.h
 *
 * Created on: Aug 2, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _CC_PROGRAMMER_H_
#define _CC_PROGRAMMER_H_

#include "cc_unit_driver.h"
#include "usb/usb_device.h"
#include "data/data_section_store.h"

struct USB_DeviceID
{
	enum { PROTOCOL_TI, PROTOCOL_CHIPCON };

	uint16_t vendor_id;
	uint16_t product_id;

	uint8_t	 endpoint_in;
	uint8_t	 endpoint_out;

	char	 description[256];
    unsigned int protocol;
};

struct CC_ProgrammerInfo
{
	std::string name;
	std::string debugger_id; // 4 unique digits
	uint16_t 	 fw_version;
	uint16_t	 fw_revision;
	USB_DeviceID usb_device;
};

typedef std::vector<USB_DeviceID> USB_DeviceIDVector;

///
class CC_Programmer : boost::noncopyable
{
public:
	enum OpenResult { OR_OK, OR_NOT_FOUND, OR_NOT_SUPPORTED };

	OpenResult open();
	OpenResult open(unsigned int bus, unsigned int device);
	[[nodiscard]] bool opened() const;
	void close();

	bool programmer_info(CC_ProgrammerInfo &info);

	[[nodiscard]] std::vector<std::string> supported_unit_names() const;
	[[nodiscard]] USB_DeviceIDVector supported_devices() const;

	enum InterfaceSpeed { IS_SLOW, IS_FAST };
	bool set_debug_interface_speed(InterfaceSpeed speed);

	bool unit_set_flash_size(unsigned int flash_size);

	void unit_status(std::string &name, bool &supported) const;
	bool unit_connect(UnitInfo &info);
	void unit_close();
	bool unit_reset();

	bool unit_locked();
	bool unit_erase();

	void unit_read_info_page(std::vector<uint8_t> &info_page);

	void unit_mac_address_read(size_t index, std::vector<uint8_t> &mac_address);

	void unit_flash_read(std::vector<uint8_t> &flash_data);
	void unit_flash_write(const DataSectionStore &sections);

	enum VerifyMethod { VM_BY_CRC, VM_BY_READ };
	bool unit_flash_verify(const DataSectionStore &sections, VerifyMethod method);

	bool unit_config_write(std::vector<uint8_t> &mac_address, std::vector<uint8_t> &lock_data);

	void unit_convert_lock_data(const std::vector<std::string> &qualifiers,
								std::vector<uint8_t>& lock_data);

	[[nodiscard]] unsigned int unit_lock_data_size() const;

	bool flash_image_embed_mac_address(DataSectionStore &sections,
			const std::vector<uint8_t> &mac_address);

	bool flash_image_embed_lock_data(DataSectionStore &sections,
			const std::vector<uint8_t> &lock_data);


	void do_on_flash_read_progress(const ProgressWatcher::OnProgress::slot_type&);
	void do_on_flash_write_progress(const ProgressWatcher::OnProgress::slot_type&);

	CC_Programmer();

private:
	void request_device_info();
	void enter_debug_mode();
	void init_device();

	CC_ProgrammerInfo programmer_info_;
	UnitInfo unit_info_;
	USB_Device usb_device_;
	std::list<std::shared_ptr<CC_UnitDriver>> unit_drivers_;
	std::shared_ptr<CC_UnitDriver> driver_;
	ProgressWatcher pw_;
};

#endif // !_CC_PROGRAMMER_H_
