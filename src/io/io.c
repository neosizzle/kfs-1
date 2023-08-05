#include "types.h"

void port_byte_out(uint16_t port, uint8_t data)
{
	__asm__("out %%al, %%dx" : :"a"(data), "d"(port));
}

uint8_t port_byte_in(uint16_t port)
{
   uint8_t ret;
   asm volatile ("inb %%dx,%%al":"=a" (ret):"d" (port));
   return ret;
}