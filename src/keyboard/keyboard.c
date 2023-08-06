#include "io.h"
#include "printk.h"
#include "keyboard.h"
#include "string.h"
#include "console.h"
#define KBD_PORT 0x60
#define MAX_SCANCODE_SIZE 0x80

int is_shift = 0;
int is_caps = 0;


struct ft_key scancode_table[MAX_SCANCODE_SIZE] = { // declaration of scancode table
	// fill array with default value
	[0x0 ... MAX_SCANCODE_SIZE - 1] = {0, 0, -1, -1},

	// fill known values
	[0x3B] = {"f1", "f1", -1 , -1},
	[0x3C] = {"f2", "f2", -1 , -1},
	[0x3D] = {"f3", "f3", -1 , -1},

	[0x29] = {"`", "~", '`', '~'},
	[0x2] = {"1", "!", '1', '!'},
	[0x3] = {"2", "@", '2', '@'},
	[0x4] = {"3", "#", '3', '#'},
	[0x5] = {"4", "$", '4', '$'},
	[0x6] = {"5", "%", '5', '%'},
	[0x7] = {"6", "^", '6', '^'},
	[0x8] = {"7", "&", '7', '&'},
	[0x9] = {"8", "*", '8', '*'},
	[0xA] = {"9", "(", '9', '('},
	[0xB] = {"0", ")", '0', ')'},
	[0xC] = {"-", "_", '-', '_'},
	[0xD] = {"=", "+", '=', '+'},
	[0xE] = {"backspace", "backspace", 8, 8},


	[0xF] = {"tab", "tab", '\t', '\t'},
	[0x10] = {"q", "Q", 'q', 'Q'},
	[0x11] = {"w", "W", 'w', 'W'},
	[0x12] = {"e", "E", 'e', 'E'},
	[0x13] = {"r", "R", 'r', 'R'},
	[0x14] = {"t", "T", 't', 'T'},
	[0x15] = {"y", "Y", 'y', 'Y'},
	[0x16] = {"u", "U", 'u', 'U'},
	[0x17] = {"i", "I", 'i', 'I'},
	[0x18] = {"o", "O", 'o', 'O'},
	[0x19] = {"p", "P", 'p', 'P'},
	[0x1A] = {"[", "{", '[', '{'},
	[0x1B] = {"]", "}", ']', '}'},
	[0x2B] = {"\\", "|", '\\', '|'},

	[0x3A] = {"caps", "caps", -1 , -1},
	[0x1E] = {"a", "A", 'a', 'A'},
	[0x1F] = {"s", "S", 's', 'S'},
	[0x20] = {"d", "D", 'd', 'D'},
	[0x21] = {"f", "F", 'f', 'F'},
	[0x22] = {"g", "G", 'g', 'G'},
	[0x23] = {"h", "H", 'h', 'H'},
	[0x24] = {"j", "J", 'j', 'J'},
	[0x25] = {"k", "K", 'k', 'K'},
	[0x26] = {"l", "L", 'l', 'L'},
	[0x1C] = {"enter", "enter", '\n', '\n'},

	[0x2A] = {"shift", "shift", -1 , -1},
	[0x2C] = {"z", "Z", 'z', 'Z'},
	[0x2D] = {"x", "X", 'x', 'X'},
	[0x2E] = {"c", "C", 'c', 'C'},
	[0x2F] = {"v", "V", 'v', 'V'},
	[0x30] = {"b", "B", 'b', 'B'},
	[0x31] = {"n", "N", 'n', 'N'},
	[0x32] = {"m", "M", 'm', 'M'},
	[0x33] = {",", "<", ',', '<'},
	[0x34] = {".", ">", '.', '>'},
	[0x35] = {"/", "?", '/', '?'},
	[0x36] = {"shift", "shift", -1 , -1},

	[0x1D] = {"ctrl", "ctrl", -1 , -1},
	[0x39] = {"space", "space", ' ', ' '},
	[0x48] = {"uparrow", "uparrow", -1, -1},
	[0x50] = {"downarrow", "downarrow", -1, -1},
	[0x4B] = {"leftarrow", "leftarrow", -1, -1},
	[0x4D] = {"rightarrow", "rightarrow", -1, -1},

	// 37 60 52 are defer signals
};

void handle_keyboard(void)
{
	int scancode = port_byte_in(KBD_PORT);
	int is_pressed = 1;
	int is_upper = -1;
	ft_key key;
	
	if (scancode >= 0x80) is_pressed = 0;
	if (!is_pressed) scancode -= 0x80;

	if (is_shift) is_upper *= -1;
	if (is_caps) is_upper *= -1;

	key = scancode_table[scancode];

	// react to key
	// if is pressed
	if (is_pressed > 0)
	{
		if (!strcmp(key.name, "f1"))
			terminal_switchscreen(0);
		else if (!strcmp(key.name, "f2"))
			terminal_switchscreen(1);
		else if (!strcmp(key.name, "f3"))
			terminal_switchscreen(2);
		else if (!strcmp(key.name, "enter"))
		{
			// enter
			console_process_buff();
			console_clear_buff();
			console_print_prompt();
		}
		else if (key.ascii > -1)
		{
			// normal keys
			if (is_upper > 0)
			{
				printk("%c", key.caps_ascii);
				console_add_to_buff(key.caps_ascii);
			}
			else
			{
				printk("%c", key.ascii);
				console_add_to_buff(key.ascii);
			}
		}

	}

	if (!strcmp("caps", key.name) && !is_pressed)
		is_caps = !is_caps;
	if (!strcmp("shift", key.name))
	{
		if (is_pressed)
			is_shift = 1;
		else
			is_shift = 0;
	}
}