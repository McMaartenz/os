#ifndef H_PAGING
#define H_PAGING

#include <stdint.h>

enum page_table_flag
{
	is_present, // 0
	is_read_write,
	is_super_user,
	is_write_through,
	is_cache_disabled,
	is_accessed,
	larger_pages = 7,
	custom0 = 9,
	custom1,
	custom2,
	NX = 63 // if supported, of course
};

struct page_directory_entry
{
	uint64_t value;
	void set_flag(page_table_flag, bool);
	bool get_flag(page_table_flag);
	void set_addr(uint64_t);
	uint64_t get_addr();
};

struct page_table
{
	page_directory_entry entries[512];
}__attribute__((aligned(0x1000)));

#endif
