#ifndef __KEYBOARD__H__
#define __KEYBOARD__H__

/**
 * ft_key - a representation of a key
 * 
 * name - name of the key
 * caps_name - capital variation of the key name
 * ascii - ascii code of key, -1 if none
 * caps_ascii - ascii code of capital key, -1 if none
*/
typedef struct ft_key {
	char *name;
	char *caps_name;
	char ascii;
	char caps_ascii;
} ft_key;

void handle_keyboard(void);

#endif  //!__KEYBOARD__H__