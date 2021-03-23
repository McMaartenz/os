#ifndef H_IO
#define H_IO

#include <stdint.h>

void byte_out(uint16_t, uint8_t);
uint8_t byte_in(uint16_t);
void io_wait();

#endif
