#ifndef KERNEL_H
# define KERNEL_H

# include "keyboard.h"

# define NB_LINES 25
# define NB_COLUMNS 80
# define BYTES_FOR_ELEMENT 2
# define SCREENSIZE BYTES_FOR_ELEMENT * NB_COLUMNS * NB_LINES

typedef struct s_terminal
{
	char			*vidptr;
	unsigned int	current_loc;
} t_terminal;

extern t_terminal terminal;

void blank_screen(void);
void write_on_screen(char *str);
void newline_on_screen(void);

#endif
