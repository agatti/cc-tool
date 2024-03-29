/*
 * cc_uint_info.h
 *
 * Created on: Aug 2, 2011
 *     Author: George Stark <george-u@yandex.com>
 *
 * License: GNU GPL v2
 *
 */

#ifndef _CC_UNIT_INFO_H_
#define _CC_UNIT_INFO_H_

#include "common.h"
#include "data/data_section.h"

struct Unit_ID
{
    unsigned int ID;
	std::string name;

	Unit_ID() : ID(0) { }
	Unit_ID(unsigned int ID_, const std::string &name_) : ID(ID_), name(name_) { }
};

struct UnitInfo
{
	enum Flags {
		SUPPORT_USB = 0x01, 		// remove
		SUPPORT_MAC_ADDRESS = 0x02, // remove, use mac_address_count to check
		SUPPORT_INFO_PAGE = 0x04
	};

    unsigned int ID;                // ID used by programmer
	std::string name;            // like 'CCxxxx'
	uint8_t internal_ID; 	// read from chip
	uint8_t revision;		// read from chip
    unsigned int flags;

    unsigned int flash_size;        // in KB
    unsigned int max_flash_size;    // in KB
	std::vector<unsigned int> flash_sizes;    // list of possible flash sizes, in KB

    unsigned int ram_size;        // in KB
    unsigned int mac_address_count;
    unsigned int mac_address_size;
    unsigned int flash_page_size; // in KB

	[[nodiscard]] size_t actual_flash_size() const;

	UnitInfo();
};

struct UnitCoreInfo
{
	size_t lock_size;		//
	size_t flash_word_size;
	size_t verify_block_size;
	size_t write_block_size;
	uint16_t xbank_offset;
	uint16_t dma0_cfg_offset;
	uint16_t dma_data_offset;

	// Xdata register addresses;
	uint16_t memctr;
	uint16_t fmap;
	uint16_t rndl;
	uint16_t rndh;
	uint16_t fctl;
	uint16_t fwdata;
	uint16_t faddrl;
	uint16_t faddrh;
	uint16_t dma0_cfgl;
	uint16_t dma0_cfgh;
	uint16_t dma_arm;
	uint16_t dma_req;
	uint16_t dma_irq;

	uint8_t fctl_write;
	uint8_t fctl_erase;

	UnitCoreInfo();
};

typedef std::list<Unit_ID> Unit_ID_List;

void check_param(bool assert, const std::string &module, unsigned int line);
#define CHECK_PARAM(x) check_param(x, __FILE__, __LINE__)

#endif // !_CC_UNIT_INFO_H_
