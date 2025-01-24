#ifndef KERNEL_H
# define KERNEL_H

# define BEGIN_VGA 0xb8000

# define NB_LINES 25
# define NB_COLUMNS 80
# define BYTES_FOR_ELEMENT 2
# define SCREENSIZE BYTES_FOR_ELEMENT * NB_COLUMNS * NB_LINES

# define LIMIT_NB_SCREENS 5

# define TAB_SIZE 4

typedef struct s_screen
{
	char	buffer[SCREENSIZE];
	int		cursor;
} t_screen;

typedef struct s_terminal
{
	char		*vidptr;
	int			cursor;
	int			current_screen;
	t_screen	screens[LIMIT_NB_SCREENS];
	int			shift;
	int			capslock;
	int			numslock;
	int			to_escape;
} t_terminal;

extern t_terminal terminal;

# include "color.h"
# include "keyboard.h"
# include "terminal.h"
# include "screen.h"
# include "string.h"
# include "printk.h"
# include "cursor.h"

#endif
