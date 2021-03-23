#ifndef H_PAGE_TABLE_MGR
#define H_PAGE_TABLE_MGR

#include <stdint.h>

#include "paging.h"
#include "page_map_indexer.h"
#include "page_frame_alloc.h"
#include "../memory.h"

class page_table_mgr
{
public:
	page_table_mgr(page_table*);
	page_table* PML4_addr;
	void map_memory(void*, void*);
};

#endif
