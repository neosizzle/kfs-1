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

typedef unsigned short int uint16_t;
typedef unsigned char uint8_t;

static void port_byte_out(uint16_t port, uint8_t data)
{
	__asm__("out %%al, %%dx" : :"a"(data), "d"(port));
}

static inline int vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}
 
static inline int vga_entry(unsigned char uc, int color) 
{
	return (int) uc | (int) color << 8;
}
 
int strlen(const char* str) 
{
	int len = 0;
	while (str[len])
		len++;
	return len;
}
 
static const int VGA_WIDTH = 80;
static const int VGA_HEIGHT = 25;
 
int terminal_row;
int terminal_column;
int terminal_color;
int* terminal_buffer;

// clear terminal
void terminal_initialize(void) 
{
	terminal_row = 0;
	terminal_column = 0;
	terminal_color = vga_entry_color(VGA_COLOR_CYAN, VGA_COLOR_BLACK);
	terminal_buffer = (int*) 0xB8000;
	for (int y = 0; y < VGA_HEIGHT; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
			const int index = y * VGA_WIDTH + x;
			terminal_buffer[index] = vga_entry(' ', terminal_color);
		}
	}
}
 
void terminal_setcolor(int color) 
{
	terminal_color = color;
}
 
void terminal_putentryat(char c, int color, int x, int y) 
{
	const int index = y * VGA_WIDTH + x;
	terminal_buffer[index] = vga_entry(c, color);
}
 
void terminal_putchar(char c) 
{
	terminal_putentryat(c, terminal_color, terminal_column, terminal_row);
	if (++terminal_column == VGA_WIDTH) {
		terminal_column = 0;
		if (++terminal_row == VGA_HEIGHT)
			terminal_row = 0;
	}
}
 
void terminal_write(const char* data, int size) 
{
	for (int i = 0; i < size; i++)
		terminal_putchar(data[i]);
}
 
void terminal_writestring(const char* data) 
{
	terminal_write(data, strlen(data));
}
 
void kernel_main(void) 
{
	/* Initialize terminal interface */
	terminal_initialize();
 
	/* Newline support is left as an exercise. */
	terminal_writestring("Hello, kernel World!");

	// change cursor
	// port_byte_out(0x3d4, 0xe);
	// port_byte_out(0x3d5, 0x00);
	// port_byte_out(0x3d4, 0xf);
	// port_byte_out(0x3d5, 0x50);

	// halt loop
	while (1)
	{
		
	}
}