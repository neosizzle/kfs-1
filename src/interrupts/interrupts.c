#include "types.h"
#include "idt.h"
#include "interrupts.h"
#include "io.h"
#include "video.h"

char *messages[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

// function to handle all software interrupts
void isr_handler(cpu_state cpu, uint32_t intr_no, uint32_t err_code, stack_state stack)
{
	// TODO check stack state is valid
	(void) cpu;
	(void) stack;

	char *msg = messages[intr_no];
	char *msg2 = messages[err_code];

	terminal_writestring(msg);
	terminal_writestring("\n");
	terminal_writestring(msg2);
	// while (1)
	// {
		
	// }
}

// function to handle all hardware interrupts
void irq_handler(cpu_state cpu, uint32_t intr_no, uint32_t err_code, stack_state stack)
{
	terminal_writestring("slayy");
	// while (1)
	// {
		
	// }
}

// enable hardware interrupts
void enable_interrupts(void)
{
	__asm__ __volatile__("sti");
}

// disable hardware interrupts
void disable_interrupts(void)
{
	__asm__ __volatile__("cli");
}

// entry calls this to init the interrupt subsystem
void init_interrupts()
{
	// isr
	create_idt_entry(0, (uint32_t)isr_handler_0);
	create_idt_entry(1, (uint32_t)isr_handler_1);
	create_idt_entry(2, (uint32_t)isr_handler_2);
	create_idt_entry(3, (uint32_t)isr_handler_3);
	create_idt_entry(4, (uint32_t)isr_handler_4);
	create_idt_entry(5, (uint32_t)isr_handler_5);
	create_idt_entry(6, (uint32_t)isr_handler_6);
	create_idt_entry(7, (uint32_t)isr_handler_7);
	create_idt_entry(8, (uint32_t)isr_handler_8);
	create_idt_entry(9, (uint32_t)isr_handler_9);
	create_idt_entry(10, (uint32_t)isr_handler_10);
	create_idt_entry(11, (uint32_t)isr_handler_11);
	create_idt_entry(12, (uint32_t)isr_handler_12);
	create_idt_entry(13, (uint32_t)isr_handler_13);
	create_idt_entry(14, (uint32_t)isr_handler_14);
	create_idt_entry(15, (uint32_t)isr_handler_15);
	create_idt_entry(16, (uint32_t)isr_handler_16);
	create_idt_entry(17, (uint32_t)isr_handler_17);
	create_idt_entry(18, (uint32_t)isr_handler_18);
	create_idt_entry(19, (uint32_t)isr_handler_19);
	create_idt_entry(20, (uint32_t)isr_handler_20);
	create_idt_entry(21, (uint32_t)isr_handler_21);
	create_idt_entry(22, (uint32_t)isr_handler_22);
	create_idt_entry(23, (uint32_t)isr_handler_23);
	create_idt_entry(24, (uint32_t)isr_handler_24);
	create_idt_entry(25, (uint32_t)isr_handler_25);
	create_idt_entry(26, (uint32_t)isr_handler_26);
	create_idt_entry(27, (uint32_t)isr_handler_27);
	create_idt_entry(28, (uint32_t)isr_handler_28);
	create_idt_entry(29, (uint32_t)isr_handler_29);
	create_idt_entry(30, (uint32_t)isr_handler_30);
	create_idt_entry(31, (uint32_t)isr_handler_31);

	// remap pic
	unsigned char a1 = port_byte_in(0x21);
	unsigned char a2 = port_byte_in(0xA1);
 
	port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    port_byte_out(0x21, a1);
    port_byte_out(0xA1, a2); 

	port_byte_out(0x21, 0xFD);

	// irq
	create_idt_entry(32 + 0, (uint32_t)irq_handler_0);
	create_idt_entry(32 + 1, (uint32_t)irq_handler_1);
	create_idt_entry(32 + 2, (uint32_t)irq_handler_2);
	create_idt_entry(32 + 3, (uint32_t)irq_handler_3);
	create_idt_entry(32 + 4, (uint32_t)irq_handler_4);
	create_idt_entry(32 + 5, (uint32_t)irq_handler_5);
	create_idt_entry(32 + 6, (uint32_t)irq_handler_6);
	create_idt_entry(32 + 7, (uint32_t)irq_handler_7);
	create_idt_entry(32 + 8, (uint32_t)irq_handler_8);
	create_idt_entry(32 + 9, (uint32_t)irq_handler_9);
	create_idt_entry(32 + 10, (uint32_t)irq_handler_10);
	create_idt_entry(32 + 11, (uint32_t)irq_handler_11);
	create_idt_entry(32 + 12, (uint32_t)irq_handler_12);
	create_idt_entry(32 + 13, (uint32_t)irq_handler_13);
	create_idt_entry(32 + 14, (uint32_t)irq_handler_14);
	create_idt_entry(32 + 15, (uint32_t)irq_handler_15);
	register_idt();
}