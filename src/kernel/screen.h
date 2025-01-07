#ifndef SCREEN_H
# define SCREEN_H

# define NB_LINES 25
# define NB_COLUMNS 80
# define BYTES_FOR_ELEMENT 2
# define SCREENSIZE BYTES_FOR_ELEMENT * NB_COLUMNS * NB_LINES

void blank_screen(void);
void newline_on_screen(void);

void printk_char(char c, int color);
void printk(char *str, int color);

char *ft_itoa(int n);

#endif
