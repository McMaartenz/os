#include "bitfield.h"

bool bitfield::operator[](uint64_t i)
{
	if (i > size * 8) return false; // prevent buffer overflow

	return ((buffer[i / 8] & (0b10000000 >> (i % 8))) > 0);
}

bool bitfield::set(uint64_t i, bool value)
{
	if (i > size * 8) return false;
	uint64_t byte_index = i / 8;
	uint8_t bit_indexer = 0b10000000 >> (i % 8);
	buffer[byte_index] &= ~bit_indexer;
	if (value)
	{
		buffer[byte_index] |= bit_indexer;
	}
	return true;
}


