#ifndef CONSOLE_H
# define CONSOLE_H

# define NB_LINES 25
# define NB_COLUMNS 80
# define BYTES_FOR_ELEMENT 2
# define SCREENSIZE BYTES_FOR_ELEMENT * NB_COLUMNS * NB_LINES

# define TAB_SIZE 4

void blank_console(void);
void newline_on_console(void);

void printk_char(char c, int color);
void printk(char *str, int color);

char *ft_itoa(int n);

#endif
