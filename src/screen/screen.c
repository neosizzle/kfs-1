#include "screen.h"
#include "video.h"
#include "string.h"

struct screen screens[MAX_SCREENS];
int current_screen;

static inline int vga_entry_color(enum vga_color fg, enum vga_color bg) 
{
	return fg | bg << 4;
}

static inline int vga_entry(unsigned char uc, int color) 
{
	return (int) uc | (int) color << 8;
}

void screens_init(void)
{
	for (int i = 0; i < MAX_SCREENS; i++)
	{
		for (int y = 0; y < VGA_HEIGHT; y++) {
			for (int x = 0; x < VGA_WIDTH; x++) {
				const int index = y * VGA_WIDTH + x;
				int def_color =  vga_entry_color(VGA_COLOR_LIGHT_GREY, VGA_COLOR_BLACK);
				screens[i].video_buffer[index] = vga_entry(' ', def_color);
				screens[i].row = 0;
				screens[i].column = 0;
				screens[i].color = def_color;
				screens[i].cursor_index = 0;
			}
		}
	}
	current_screen = 0;
}

struct screen get_screen(void)
{
	return screens[current_screen];
}

void screen_clear(void)
{
	for (int y = 0; y < VGA_HEIGHT; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
			const int index = y * VGA_WIDTH + x;
			screens[current_screen].video_buffer[index] = vga_entry(' ', screens[current_screen].color);
		}
	}
	screens[current_screen].cursor_index = 0;
}

void screen_setcolor(int color)
{
	screens[current_screen].color = color;
}

void screen_putentry_at(char c, int color, int x, int y)
{
	const int index = y * VGA_WIDTH + x;
	screens[current_screen].video_buffer[index] = vga_entry(c, color);

	// change cursors
	++screens[current_screen].cursor_index;
}

void screen_putchar(char c, int color) 
{
	(void) color;
	
	// newline support
	if (c == '\n')
	{
		screens[current_screen].column = 0;
		++screens[current_screen].row;

		// change cursors
		screens[current_screen].cursor_index = (screens[current_screen].row * VGA_WIDTH);
		
		// limit check
		if (screens[current_screen].row == VGA_HEIGHT)
		{
			screen_clear();
			screens[current_screen].row = 0;
		}
		return;
	}
	// limit check
	if (++screens[current_screen].column == VGA_WIDTH) {
		screens[current_screen].column = 0;
		if (++screens[current_screen].row == VGA_HEIGHT)
		{
			screen_clear();
			screens[current_screen].row = 0;
		}
	}
}

int screen_switch(int idx)
{
	if (idx < 0 || idx >= MAX_SCREENS)
		return -1;
	current_screen = idx;
	return 0;
}

static void screen_clear_at(int idx)
{
	for (int y = 0; y < VGA_HEIGHT; y++) {
		for (int x = 0; x < VGA_WIDTH; x++) {
			const int index = y * VGA_WIDTH + x;
			screens[idx].video_buffer[index] = vga_entry(' ', screens[idx].color);
		}
	}
	screens[idx].cursor_index = 0;
}

static void screen_putentry_at_screen(char c, int color, int x, int y, int screen)
{
	const int index = y * VGA_WIDTH + x;
	screens[screen].video_buffer[index] = vga_entry(c, color);

	// change cursors
	++screens[screen].cursor_index;	
}

static void screen_putchar_rest(char c, int color) 
{
	for (int i = 0; i < MAX_SCREENS; i++)
	{
		if (i == current_screen)
			continue ;
		// newline support
		if (c == '\n')
		{
			screens[i].column = 0;
			++screens[i].row;

			// change cursors
			screens[i].cursor_index = (screens[i].row * VGA_WIDTH);
			
			// limit check
			if (screens[i].row == VGA_HEIGHT)
			{
				screen_clear_at(i);
				screens[i].row = 0;
			}
			continue;
		}
		screen_putentry_at_screen(c, color, screens[i].column, screens[i].row, i);
		// limit check
		if (++screens[i].column == VGA_WIDTH) {
			screens[i].column = 0;
			if (++screens[i].row == VGA_HEIGHT)
			{
				screen_clear_at(i);
				screens[i].row = 0;
			}
		}
	}
	
}

void screen_writestring_color_rest(char *str, int color)
{
	for (int i = 0; i < strlen(str); i++)
		screen_putchar_rest(str[i], color);
}

int get_curr_screen(void)
{
	return current_screen;
}