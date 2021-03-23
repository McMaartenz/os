#include "page_map_indexer.h"

page_map_indexer::page_map_indexer(uint64_t virtual_addr)
{
	virtual_addr >>= 12;
	page_i = virtual_addr & 0x1ff;

	virtual_addr >>= 9;
	page_table_i = virtual_addr & 0x1ff;

	virtual_addr >>= 9;
	page_directory_i = virtual_addr & 0x1ff;

	virtual_addr >>= 9;
	page_directory_ptr_i = virtual_addr & 0x1ff;
}
