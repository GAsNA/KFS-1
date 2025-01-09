#ifndef KERNEL_H
# define KERNEL_H

# include "color.h"
# include "keyboard.h"
# include "console.h"

# define LIMIT_NB_SCREENS 5

typedef struct s_screen
{
	char	*buffer;
	int	current_loc;
} t_screen;

typedef struct s_terminal
{
	char		*vidptr;
	int		current_screen;
	t_screen	screens[LIMIT_NB_SCREENS];
	int		current_loc;
	int		shift;
	int		capslock;
	int		numslock;
} t_terminal;

extern t_terminal terminal;

#endif
