#ifndef H_FRAMEBUFFER
#define H_FRAMEBUFFER

#include <stddef.h>

struct Framebuffer
{
	void* baseAddr;
	size_t bufferSize;
	unsigned int width;
	unsigned int height;
	unsigned int ppscln;
	unsigned int BPP;
};

#endif
