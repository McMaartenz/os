#ifndef H_PAGE_FRAME_ALLOC
#define H_PAGE_FRAME_ALLOC

#include <stdint.h>

#include "../efi_memory.h"
#include "../bitfield.h"
#include "../memory.h"

class page_frame_alloc
{
public:
	void read_efi_memory_map(EFI_MEMORY_DESCRIPTOR*, size_t, size_t);
	bitfield page_bf;	
	void page_free(void*);
	void pages_free(void*, uint64_t);
	void page_lock(void*);
	void pages_lock(void*, uint64_t);
	
	void* page_request();
	
	uint64_t get_mem_free();
	uint64_t get_mem_used();
	uint64_t get_mem_reserved();

private:
	void initialize_bitfield(size_t, void*);
	void page_reserve(void*);
	void pages_reserve(void*, uint64_t);
	void page_unreserve(void*);
	void pages_unreserve(void*, uint64_t);
};

extern page_frame_alloc global_alloc;

#endif
