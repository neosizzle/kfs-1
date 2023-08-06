#ifndef __CONSOLE__H__
#define __CONSOLE__H__

void init_console(void);
void console_clear_buff(void);
void console_add_to_buff(char c);
int console_process_buff(void);
void console_print_prompt(void);

#endif  //!__CONSOLE__H__