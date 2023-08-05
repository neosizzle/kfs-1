#include "types.h"
#include "interrupts.h"
#include "io.h"
#include "string.h"
#include "video.h"
#include "printk.h"

void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
 
	/* Print banner */
	printk("%s %c%d!\n", "Hello", '4', 2);

	/* Initialize interrupts */
	init_interrupts();

	/* Enable interrupts */
	enable_interrupts();

	// halt loop
	while (1)
	{
		
	}
}