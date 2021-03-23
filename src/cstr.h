#ifndef H_CSTR
#define H_CSTR

#include <stdint.h>

uint8_t str_length(const char*);

const char* to_s(uint64_t);
const char* to_s(int64_t);
const char* to_s(double, int8_t = 2);
const char* to_s(float, int8_t = 2);

const char* to_hs(uint64_t);
const char* to_hs(uint32_t);
const char* to_hs(uint16_t);
const char* to_hs(uint8_t);

#endif
