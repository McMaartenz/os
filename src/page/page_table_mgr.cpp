#include "page_table_mgr.h"

page_table_mgr::page_table_mgr(page_table* PML4_addr)
{
	this->PML4_addr = PML4_addr;
}

void page_table_mgr::map_memory(void* virtual_addr, void* physical_addr)
{
	page_map_indexer indexer = page_map_indexer((uint64_t)virtual_addr);
	page_directory_entry pd_entry;

	pd_entry = PML4_addr->entries[indexer.page_directory_ptr_i];
	page_table* page_directory_ptr;

	if (!pd_entry.get_flag(page_table_flag::is_present))
	{
		page_directory_ptr = (page_table*)global_alloc.page_request();
		set_memory(page_directory_ptr, 0, 0x1000);
		pd_entry.set_addr((uint64_t)page_directory_ptr >> 12);
		pd_entry.set_flag(page_table_flag::is_present, true);
		pd_entry.set_flag(page_table_flag::is_read_write, true);
		PML4_addr->entries[indexer.page_directory_ptr_i] = pd_entry;
	}
	else
	{
		page_directory_ptr = (page_table*)((uint64_t)pd_entry.get_addr() << 12);
	}
	
	pd_entry = page_directory_ptr->entries[indexer.page_directory_i];
	page_table* page_directory;

	if (!pd_entry.get_flag(page_table_flag::is_present))
	{
		page_directory = (page_table*)global_alloc.page_request();
		set_memory(page_directory, 0, 0x1000);
		pd_entry.set_addr((uint64_t)page_directory >> 12);
		pd_entry.set_flag(page_table_flag::is_present, true);
		pd_entry.set_flag(page_table_flag::is_read_write, true);
		page_directory_ptr->entries[indexer.page_directory_i] = pd_entry;
	}
	else
	{
		page_directory = (page_table*)((uint64_t)pd_entry.get_addr() << 12);
	}
	
	pd_entry = page_directory->entries[indexer.page_table_i];
	page_table* p_table;

	if (!pd_entry.get_flag(page_table_flag::is_present))
	{
		p_table = (page_table*)global_alloc.page_request();
		set_memory(p_table, 0, 0x1000);
		pd_entry.set_addr((uint64_t)p_table >> 12);
		pd_entry.set_flag(page_table_flag::is_present, true);
		pd_entry.set_flag(page_table_flag::is_read_write, true);
		page_directory->entries[indexer.page_table_i] = pd_entry;
	}
	else
	{
		p_table = (page_table*)((uint64_t)pd_entry.get_addr() << 12);
	}
	
	pd_entry = p_table->entries[indexer.page_i];
	pd_entry.set_addr((uint64_t)physical_addr >> 12);
	pd_entry.set_flag(page_table_flag::is_present, true);
	pd_entry.set_flag(page_table_flag::is_read_write, true);

	p_table->entries[indexer.page_i] = pd_entry;
}
