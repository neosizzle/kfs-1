#ifndef __IDT__H__
#define __IDT__H__

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
extern idt_entry idt_entries[NUM_IDT_ENTRIES];

// idt table itself
extern idt_table _idt_table;

#endif  //!__IDT__H__