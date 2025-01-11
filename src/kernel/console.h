#ifndef CONSOLE_H
# define CONSOLE_H

void clear_console(void);
void newline_on_console(void);
void delete_on_console(void);
void tab_on_console(void);

void print_char_on_console(char c, int color);
void print_on_console(char *str, int color);

#endif
