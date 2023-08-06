#ifndef __IDT__H__
#define __IDT__H__

/**
 * How every idt entry is defined
*/
typedef struct __attribute__((packed)) idt_entry {
	uint16_t offset_low; // low offset
	uint16_t segment_sel; // segment selector
	uint8_t always_zero; // always zero bytes, including reserved bytes
	uint8_t flags; // flags
	uint16_t offset_high; // high offset
} idt_entry;

/**
 * The IDT table itself
*/
typedef struct __attribute__((packed)) idt_table {
	uint16_t limit; // how many entries this table has?
	uint32_t base; // address of the first entry
} idt_table;

// array of idt entries
extern idt_entry idt_entries[256];

// idt table itself
extern idt_table _idt_table;

void create_idt_entry(int index, uint32_t handler);
void register_idt(void);

// array of isr handler functions (declared in asm)
extern void isr_handler_0();
extern void isr_handler_1();
extern void isr_handler_2();
extern void isr_handler_3();
extern void isr_handler_4();
extern void isr_handler_5();
extern void isr_handler_6();
extern void isr_handler_7();
extern void isr_handler_8();
extern void isr_handler_9();
extern void isr_handler_10();
extern void isr_handler_11();
extern void isr_handler_12();
extern void isr_handler_13();
extern void isr_handler_14();
extern void isr_handler_15();
extern void isr_handler_16();
extern void isr_handler_17();
extern void isr_handler_18();
extern void isr_handler_19();
extern void isr_handler_20();
extern void isr_handler_21();
extern void isr_handler_22();
extern void isr_handler_23();
extern void isr_handler_24();
extern void isr_handler_25();
extern void isr_handler_26();
extern void isr_handler_27();
extern void isr_handler_28();
extern void isr_handler_29();
extern void isr_handler_30();
extern void isr_handler_31();

// array of irq handler functs
extern void irq_handler_0();
extern void irq_handler_1();
extern void irq_handler_2();
extern void irq_handler_3();
extern void irq_handler_4();
extern void irq_handler_5();
extern void irq_handler_6();
extern void irq_handler_7();
extern void irq_handler_8();
extern void irq_handler_9();
extern void irq_handler_10();
extern void irq_handler_11();
extern void irq_handler_12();
extern void irq_handler_13();
extern void irq_handler_14();
extern void irq_handler_15();

#endif  //!__IDT__H__