#ifndef H_BITFIELD
#define H_BITFIELD

#include <stddef.h>
#include <stdint.h>

class bitfield
{
public:
	size_t size;
	uint8_t* buffer;
	bool operator[](uint64_t);
	bool set(uint64_t, bool);
};

#endif
