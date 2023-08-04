#ifndef __INTERRUPTS__H__
#define __INTERRUPTS__H__

void init_interrupts(void);

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

#endif  //!__INTERRUPTS__H__