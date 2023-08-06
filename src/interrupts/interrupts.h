#ifndef __INTERRUPTS__H__
#define __INTERRUPTS__H__

/* this struct is created using pusha from the asm interrupt handler */
typedef struct __attribute__((packed)) cpu_state {
   uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; /* Pushed by pusha. */
}  cpu_state;


/**
 * this struct will be created automatically by processpor
 * when calling to the handler function
*/
typedef struct __attribute__((packed)) stack_state {
	uint32_t error_code;
	uint32_t eip;
	uint32_t cs; // segment selector, needed to generate idt entry
	uint32_t eflags;
}  stack_state;

void init_interrupts(void);
void enable_interrupts(void);
void disable_interrupts(void);

#endif  //!__INTERRUPTS__H__