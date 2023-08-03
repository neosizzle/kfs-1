#include "types.h"

/* this struct is created using pusha from the asm interrupt handler */
typedef struct __attribute__((packed)) cpu_state {
   u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
}  cpu_state;


/**
 * this struct will be created automatically by processpor
 * when calling to the handler function
*/
typedef struct __attribute__((packed)) stack_state {
	u32 error_code;
	u32 eip;
	u32 cs; // segment selector, needed to generate idt entry
	u32 eflags;
}  stack_state;

void terminal_writestring(const char* data) ;

// function to handle all interrupts
void isr_handler(struct cpu_state cpu, struct stack_state stack, u32 interrupt_no, u32 err_code)
{
	terminal_writestring("yike");
}

// entry calls this to init the interrupt subsystem
void init_interrupts()
{

}