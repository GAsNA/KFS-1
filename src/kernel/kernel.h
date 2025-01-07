#ifndef KERNEL_H
# define KERNEL_H

# include "color.h"
# include "keyboard.h"
# include "screen.h"

typedef struct s_terminal
{
	char		*vidptr;
	unsigned int	current_loc;
	int		shift;
	int		capslock;
	int		numslock;
} t_terminal;

extern t_terminal terminal;

#endif
