
#include "string.h"
#include "io.h"
#include "types.h"
#include "video.h"

static const int VGA_WIDTH = 40;
static const int VGA_HEIGHT = 25;

int terminal_row;
int terminal_column;
int terminal_color;
int* terminal_buffer;
int cursor_index;


static inline int vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline int vga_entry(unsigned char uc, int color) 
{
	return (int) uc | (int) color << 8;
}

void put_cursor_at(int idx)
{
	port_byte_out(0x3d4, 0xe);
	port_byte_out(0x3d5, high_8(idx));
	port_byte_out(0x3d4, 0xf);
	port_byte_out(0x3d5, low_8(idx));
}

void terminal_clear(void)
{
	for (int y = 0; y < VGA_HEIGHT; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
			const int index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
	cursor_index = 0;
	put_cursor_at(cursor_index);
}

void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
	terminal_buffer = (int*) 0xB8000;
	cursor_index = 0;
	terminal_clear();
}

void terminal_setcolor(int color) 
{
	terminal_color = color;
}

void terminal_putentryat(char c, int color, int x, int y) 
{
	const int index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);

	// change cursors
	cursor_index += 2;
	put_cursor_at(cursor_index);
}
 
void terminal_putchar(char c, int color) 
{
	// newline support
	if (c == '\n')
	{
		terminal_column = 0;
		++terminal_row;

		// change cursors
		cursor_index = 2 * (terminal_row * VGA_WIDTH);
		put_cursor_at(cursor_index);
		
		// limit check
		if (terminal_row == VGA_HEIGHT)
		{
			terminal_clear();
			terminal_row = 0;
		}
		return;
	}
	terminal_putentryat(c, color, terminal_column, terminal_row);
	// limit check
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
		{
			terminal_clear();
			terminal_row = 0;
		}
	}
}

void terminal_write(const char* data, int size) 
{
	for (int i = 0; i < size; i++)
		terminal_putchar(data[i], terminal_color);
}

void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}