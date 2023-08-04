#include "types.h"
#include "idt.h"

// array of idt entries
#define NUM_IDT_ENTRIES 256
idt_entry idt_entries[NUM_IDT_ENTRIES];

// idt table itself
idt_table _idt_table;

// create handler for an entry
void create_idt_entry(int index, u32 handler)
{
	unsigned short cs;
    __asm__ ("mov %%cs, %0" : "=r" (cs));

	idt_entries[index].offset_low = low_16(handler);
	idt_entries[index].segment_sel = cs;
	idt_entries[index].always_zero = 0;
	idt_entries[index].flags = 0x8E; // tbd find out why
	idt_entries[index].offset_high = high_16(handler);
}

// register thr IDT. from this point on, interrupt handlers will run
void register_idt()
{
	_idt_table.base = (u32) &idt_entries;
	_idt_table.limit = NUM_IDT_ENTRIES * sizeof(idt_entries) - 1;
	__asm__ __volatile__("lidtl (%0)" : : "r" (&_idt_table));
}