#ifndef __VIDEO__H__
#define __VIDEO__H__

void terminal_initialize(void);
void terminal_setcolor(int color);
void terminal_putentryat(char c, int color, int x, int y);
void terminal_putchar(char c);
void terminal_write(const char* data, int size);
void terminal_writestring(const char* data);

#endif  //!__VIDEO__H__