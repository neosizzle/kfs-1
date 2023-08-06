#include "video.h"
#include "printk.h"
#include "screen.h"

char console_buff[1024];
int console_buff_idx;

struct console_input {
	char console_buff[1024];
	int console_buff_idx;
}
struct console_inputs[MAX_SCREENS];

static void console_clear_buff_all(void)
{
	for (int i = 0; i < MAX_SCREENS; i++)
	{
		for (int j = 0; j < 1024; j++)
			console_inputs[i].console_buff[j] = 0;
		console_inputs[i].console_buff_idx = 0;
	}
	
}

void console_clear_buff(void)
{
	int curr_screen = get_curr_screen();

	for (int i = 0; i < 1024; i++)
		console_inputs[current_screen].console_buff[i] = 0;
	console_inputs[current_screen].console_buff_idx = 0;
}

void console_print_prompt(void)
{
	terminal_writestring_color("[jng@kfs1]", VGA_COLOR_CYAN);
	terminal_writestring("$ ");
}

void console_print_prompt_rest(void)
{
	screen_writestring_color_rest("[jng@kfs1]", VGA_COLOR_CYAN);
	screen_writestring_color_rest("$ ", VGA_COLOR_LIGHT_GREY);
}

/**
 * Init console, prints prompt
*/
void init_console(void)
{
	console_print_prompt();
	console_print_prompt_rest();
	console_clear_buff_all();
}

void console_add_to_buff(char c)
{
	int curr_screen = get_curr_screen();

	if (console_inputs[current_screen].console_buff_idx >= 1023)
		return;
	console_inputs[current_screen].console_buff[console_inputs[current_screen].console_buff_idx++] = c;
}

int console_process_buff(void)
{
	printk("\n%s\n", console_inputs[current_screen].console_buff);
	return 0;
}