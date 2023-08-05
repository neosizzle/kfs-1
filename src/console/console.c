#include "video.h"

char console_buff[1024];
int console_buff_idx;

void console_clear_buff(void)
{
	for (int i = 0; i < 1024; i++)
		console_buff[i] = 0;
	console_buff_idx = 0;
}

void console_print_prompt(void)
{
	terminal_writestring_color("[jng@kfs1]", VGA_COLOR_CYAN);
	terminal_writestring("$ ");
}

/**
 * Init console, prints prompt
*/
void init_console(void)
{
	console_print_prompt();
	console_clear_buff();
	console_buff_idx = 0;
}

void console_add_to_buff(char c)
{
	if (console_buff_idx >= 1023)
		return;
	console_buff[console_buff_idx++] = c;
}

int console_process_buff(void)
{
	printk("\n%s\n", console_buff);
	return 0;
}