/*
 * usb_device.h
 *
 * Created on: Aug 2, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _USB_DEVICE_H_
#define _USB_DEVICE_H_

#include <memory>

#include <libusb-1.0/libusb.h>
#include "common.h"

typedef std::shared_ptr<libusb_context> USB_ContextPtr;

class USB_Device : boost::noncopyable
{
public:
	enum DebugLevel { DL_OFF = 0, DL_ERROR, DL_WARNING, DL_INFORMATION };
	void set_debug_mode(DebugLevel level);

	void set_transfer_timeout(unsigned int timeout);

	void reset_device();

	void set_configuration(unsigned int configuration); // throw
	void claim_interface(unsigned int interface_number); // throw
	void release_interface(unsigned int interface_number); // throw

	void device_descriptor(libusb_device_descriptor &descriptor); // throw
	void string_descriptor_utf8(uint8_t index, uint16_t language, std::string &data); // throw
	void string_descriptor_ascii(uint8_t index, std::string &data); // throw

	void clear_halt(uint8_t endpoint);

	void bulk_read(uint8_t endpoint, size_t count, uint8_t data[]); // throw
	void bulk_write(uint8_t endpoint, size_t count, const uint8_t data[]); // throw

	void control_write(uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue,
			uint16_t wIndex, const uint8_t data[], size_t count); // throw

	void control_read(uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue,
			uint16_t wIndex, uint8_t data[], size_t count); // throw

	bool open_by_vid_pid(uint16_t vendor_id, uint16_t product_id); // throw
	bool open_by_address(uint8_t bus_number, uint8_t device_address); // throw
	[[nodiscard]] bool opened() const;
	void close();

	USB_Device();
	~USB_Device();

private:
	void init_context();
	void check_open();

	USB_ContextPtr context_;
	libusb_device_handle *handle_;
	libusb_device *device_;
	unsigned int timeout_;
};

#endif // !_USB_DEVICE_H_
