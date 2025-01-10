#ifndef KERNEL_H
# define KERNEL_H

# define BEGIN_VGA 0xb8000

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

# include "color.h"
# include "keyboard.h"
# include "console.h"
# include "screen.h"
# include "string.h"

#endif
