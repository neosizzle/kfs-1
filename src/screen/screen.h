#ifndef __SCREEN__H__
#define __SCREEN__H__
#include "types.h"

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_CAPACITY VGA_WIDTH * VGA_HEIGHT
#define MAX_SCREENS 3


struct screen {
	uint16_t video_buffer[VGA_CAPACITY];
	int row;
	int column;
	int color;
	int cursor_index;
};

void screens_init(void);
struct screen get_screen(void);
void screen_clear(void);
void screen_setcolor(int color);
void screen_putentry_at(char c, int color, int x, int y);
void screen_putchar(char c, int color);
int screen_switch(int idx);
void screen_writestring_color_rest(char *str, int color);
int get_curr_screen(void);

#endif  //!__SCREEN__H__