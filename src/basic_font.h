#ifndef H_BASIC_FONT
#define H_BASIC_FONT

struct PSF1_HEADER
{
	unsigned char magic[2];
	unsigned char mode;
	unsigned char char_size;
};

struct PSF1_FONT
{
	PSF1_HEADER* psf1_header;
	void* glyph_buffer;
};

#endif
