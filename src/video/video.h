#ifndef __VIDEO__H__
#define __VIDEO__H__


/* Hardware text mode color constants. */
enum vga_color {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
};

void terminal_initialize(void);
void terminal_setcolor(int color);
void terminal_putentryat(char c, int color, int x, int y);
void terminal_putchar(char c, int color);
void terminal_write(const char* data, int size);
void terminal_writestring(const char* data);
void terminal_clear(void);
void terminal_writestring_color(const char* data,int color);

#endif  //!__VIDEO__H__