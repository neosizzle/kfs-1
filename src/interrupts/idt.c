#include "types.h"

/**
 * How every idt entry is defined
*/
typedef struct __attribute__((packed)) idt_entry {
	u16 offset_low; // low offset
	u16 segment_sel; // segment selector
	u8 always_zero; // always zero bytes, including reserved bytes
	u8 flags; // flags
	u16 offset_high; // high offset
} idt_entry;

/**
 * The IDT table itself
*/
typedef struct __attribute__((packed)) idt_table {
	u16 limit; // how many entries this table has?
	u32 base; // address of the first entry
} idt_table;

// array of idt entries
#define NUM_IDT_ENTRIES 256
idt_entry idt_entries[NUM_IDT_ENTRIES];

// idt table itself
idt_table _idt_table;

// create handler for an entry
void create_idt_entry(int index, u32 handler)
{

}

// register thr IDT. from this point on, interrupt handlers will run
void register_idt()
{

}
