#ifndef KERNEL_H
# define KERNEL_H

# include "color.h"
# include "keyboard.h"
# include "console.h"

typedef struct s_terminal
{
	char		*vidptr;
	int		current_loc;
	int		shift;
	int		capslock;
	int		numslock;
} t_terminal;

extern t_terminal terminal;

#endif
