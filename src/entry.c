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
	terminal_writestring("Hello 42!\n");
	

	/* Initialize interrupts */
	init_interrupts();

	/* Enable interrupts */
	enable_interrupts();

	// halt loop
	while (1)
	{
		
	}
}