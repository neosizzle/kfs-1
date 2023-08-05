#include "types.h"
#include "interrupts.h"
#include "io.h"
#include "string.h"
#include "video.h"
 
void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
 
	// change cursor
	// port_byte_out(0x3d4, 0xe);
	// port_byte_out(0x3d5, 0x00);
	// port_byte_out(0x3d4, 0xf);
	// port_byte_out(0x3d5, 0x50);

	// init interrupts
	init_interrupts();

	// test int 0

	// enable interrupt
	enable_interrupts();

	// halt loop
	while (1)
	{
		
	}
}