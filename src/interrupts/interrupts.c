#include "types.h"
#include "idt.h"
#include "interrupts.h"

void terminal_writestring(const char* data) ;
void port_byte_out(u16 port, u8 data);

static inline u8 inb(u16 port)
{
    u8 ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}


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
void isr_handler(cpu_state cpu, u32 err_code, u32 intr_no, stack_state stack)
{
	// TODO check stack state is valid
	(void) cpu;
	(void) stack;

	char *msg = messages[intr_no];
	char *msg2 = messages[err_code];

	// terminal_writestring(msg);
	terminal_writestring(msg2);
	// while (1)
	// {
		
	// }
}

// function to handle all hardware interrupts
void irq_handler(cpu_state cpu, u32 err_code, u32 intr_no, stack_state stack)
{
	terminal_writestring("slayy");
}

// entry calls this to init the interrupt subsystem
void init_interrupts()
{
	// isr
	create_idt_entry(0, (u32)isr_handler_0);
	create_idt_entry(1, (u32)isr_handler_1);
	create_idt_entry(2, (u32)isr_handler_2);
	create_idt_entry(3, (u32)isr_handler_3);
	create_idt_entry(4, (u32)isr_handler_4);
	create_idt_entry(5, (u32)isr_handler_5);
	create_idt_entry(6, (u32)isr_handler_6);
	create_idt_entry(7, (u32)isr_handler_7);
	create_idt_entry(8, (u32)isr_handler_8);
	create_idt_entry(9, (u32)isr_handler_9);
	create_idt_entry(10, (u32)isr_handler_10);
	create_idt_entry(11, (u32)isr_handler_11);
	create_idt_entry(12, (u32)isr_handler_12);
	create_idt_entry(13, (u32)isr_handler_13);
	create_idt_entry(14, (u32)isr_handler_14);
	create_idt_entry(15, (u32)isr_handler_15);
	create_idt_entry(16, (u32)isr_handler_16);
	create_idt_entry(17, (u32)isr_handler_17);
	create_idt_entry(18, (u32)isr_handler_18);
	create_idt_entry(19, (u32)isr_handler_19);
	create_idt_entry(20, (u32)isr_handler_20);
	create_idt_entry(21, (u32)isr_handler_21);
	create_idt_entry(22, (u32)isr_handler_22);
	create_idt_entry(23, (u32)isr_handler_23);
	create_idt_entry(24, (u32)isr_handler_24);
	create_idt_entry(25, (u32)isr_handler_25);
	create_idt_entry(26, (u32)isr_handler_26);
	create_idt_entry(27, (u32)isr_handler_27);
	create_idt_entry(28, (u32)isr_handler_28);
	create_idt_entry(29, (u32)isr_handler_29);
	create_idt_entry(30, (u32)isr_handler_30);
	create_idt_entry(31, (u32)isr_handler_31);

	// remap pic
	unsigned char a1 = inb(0x21);
	unsigned char a2 = inb(0xA1);
 
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
	create_idt_entry(32 + 0, (u32)irq_handler_0);
	create_idt_entry(32 + 1, (u32)irq_handler_1);
	create_idt_entry(32 + 2, (u32)irq_handler_2);
	create_idt_entry(32 + 3, (u32)irq_handler_3);
	create_idt_entry(32 + 4, (u32)irq_handler_4);
	create_idt_entry(32 + 5, (u32)irq_handler_5);
	create_idt_entry(32 + 6, (u32)irq_handler_6);
	create_idt_entry(32 + 7, (u32)irq_handler_7);
	create_idt_entry(32 + 8, (u32)irq_handler_8);
	create_idt_entry(32 + 9, (u32)irq_handler_9);
	create_idt_entry(32 + 10, (u32)irq_handler_10);
	create_idt_entry(32 + 11, (u32)irq_handler_11);
	create_idt_entry(32 + 12, (u32)irq_handler_12);
	create_idt_entry(32 + 13, (u32)irq_handler_13);
	create_idt_entry(32 + 14, (u32)irq_handler_14);
	create_idt_entry(32 + 15, (u32)irq_handler_15);
	register_idt();
}