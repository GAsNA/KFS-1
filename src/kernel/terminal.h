#ifndef TERMINAL_H
# define TERMINAL_H

void init_terminal(void);

void clear_terminal(void);
void newline_on_terminal(void);
void delete_on_terminal(void);
void tab_on_terminal(void);

void move_buffer_terminal_to_left(int n);

void print_char_on_terminal(char c, int color);
void print_on_terminal(char *str, int color);

#endif
