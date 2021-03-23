#ifndef H_PAGE_MAP_INDEXER
#define H_PAGE_MAP_INDEXER

#include <stdint.h>

class page_map_indexer
{
public:
	page_map_indexer(uint64_t);
	uint64_t page_directory_ptr_i;
	uint64_t page_directory_i;
	uint64_t page_table_i;
	uint64_t page_i;
};

#endif
