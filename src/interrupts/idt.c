#include "types.h"
#include "idt.h"

idt_entry idt_entries[256];

// idt table itself
idt_table _idt_table;

// create handler for an entry
void create_idt_entry(int index, uint32_t handler)
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
	_idt_table.base = (uint32_t) &idt_entries;
	_idt_table.limit = 256 * sizeof(idt_entries) - 1;
	__asm__ __volatile__("lidtl (%0)" : : "r" (&_idt_table));
}
