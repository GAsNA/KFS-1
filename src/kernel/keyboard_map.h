#ifndef KEYBOARD_MAP_H
# define KEYBOARD_MAP_H

enum Keycode {
	ERROR,
	ESCAPE,
	ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, ZERO, DASH, EQUAL, BACKSPACE,
	TAB, Q, W, E, R, T, Y, U, I, O, P, LBRACKET, RBRACKET,
	ENTER,
	LCTRL,
	A, S, D, F, G, H, J, K, L, SEMICOLON, SINGLEQUOTE,
	GRAVEACCENT,
	LSHIFT,
	BACKSLASH,
	Z, X, C, V, B, N, M, COMMA, POINT, SLASH, RSHIFT,
	ASTERISK,
	LALT, SPACEBAR,
	CAPSLOCK,
	F1, F2, F3, F4, F5, F6, F7, F8, F9, F10,
	NUMSLOCK,
	SCROLLLOCK,
	KEYPAD7, KEYPAD8, KEYPAD9,
	MINUS,
	KEYPAD4, KEYPAD5, KEYPAD6, PLUS,
	KEYPAD1, KEYPAD2, KEYPAD3,
	KEYPAD0, KEYPADPOINT,
	IGNORE1, IGNORE2, IGNORE3,
	F11, F12,
	UNDEFINED,
};

typedef struct s_key
{
	int	small;
	int	capital;
} t_key;

t_key keyboard_map[128] =
{
	{ .small = 0, .capital = 0 },		/* ERROR */
	{ .small = 27, .capital = 27 },		/* ESCAPE */
	{ .small = '1', .capital = '!' },
	{ .small = '2', .capital = '@' },
	{ .small = '3', .capital = '#' },
	{ .small = '4', .capital = '$' },
	{ .small = '5', .capital = '%' },
	{ .small = '6', .capital = '^' },
	{ .small = '7', .capital = '&' },
	{ .small = '8', .capital = '*' },
	{ .small = '9', .capital = '(' },
	{ .small = '0', .capital =')' },
	{ .small = '-', .capital = '_' },
	{ .small = '=', .capital = '+' },
	{ .small = '\b', .capital = '\b' },	/* BACKSPACE */
	{ .small = '\t', .capital = '\t' },	/* TAB */
	{ .small = 'q', .capital = 'Q' },
	{ .small = 'w', .capital = 'W' },
	{ .small = 'e', .capital = 'E' },
	{ .small = 'r', .capital = 'R' },
	{ .small = 't', .capital = 'T' },
	{ .small = 'y', .capital = 'Y' },
	{ .small = 'u', .capital = 'U' },
	{ .small = 'i', .capital = 'I' },
	{ .small = 'o', .capital = 'O' },
	{ .small = 'p', .capital = 'P' },
	{ .small = '[', .capital = '{' },
	{ .small = ']', .capital = '}' },
	{ .small = '\n', .capital = '\n' },	/* ENTER */
	{ .small = 0, .capital = 0 },		/* LCRTL */
	{ .small = 'a', .capital = 'A' },
	{ .small = 's', .capital = 'S' },
	{ .small = 'd', .capital = 'D' },
	{ .small = 'f', .capital = 'F' },
	{ .small = 'g', .capital = 'G' },
	{ .small = 'h', .capital = 'H' },
	{ .small = 'j', .capital = 'J' },
	{ .small = 'k', .capital = 'K' },
	{ .small = 'l', .capital = 'L' },
	{ .small = ';', .capital = ':' },
	{ .small = '\'', .capital = '\"' },
	{ .small = '`', .capital = '~' },
	{ .small = 0, .capital = 0 },		/* LSHIFT */
	{ .small = '\\', .capital = '|' },
	{ .small = 'z', .capital = 'Z' },
	{ .small = 'x', .capital = 'X' },
	{ .small = 'c', .capital = 'C' },
	{ .small = 'v', .capital = 'V' },
	{ .small = 'b', .capital = 'B' },
	{ .small = 'n', .capital = 'N' },
	{ .small = 'm', .capital = 'M' },
	{ .small = ',', .capital = '<' },
	{ .small = '.', .capital = '>' },
	{ .small = '/', .capital = '?' },
	{ .small = 0, .capital = 0 },		/* RSHIFT */
	{ .small = '*', .capital = '*' },
	{ .small = 0, .capital = 0 },		/* LALT */
	{ .small = ' ', .capital = ' ' },
	{ .small = 0, .capital = 0 },		/* CAPSLOCK */
	{ .small = 0, .capital = 0 },		/* F1... */
	{ .small = 0, .capital = 0 },
	{ .small = 0, .capital = 0 },
	{ .small = 0, .capital = 0 },
	{ .small = 0, .capital = 0 },
	{ .small = 0, .capital = 0 },
	{ .small = 0, .capital = 0 },
	{ .small = 0, .capital = 0 },
	{ .small = 0, .capital = 0 },
	{ .small = 0, .capital = 0 },		/* F10... */
	{ .small = 0, .capital = 0 },		/* NUMSLOCK */
	{ .small = 0, .capital = 0 },		/* SCROLLLOCK */
	{ .small = 0, .capital = 0 },		/* KEYPAD7 */
	{ .small = 0, .capital = 0 },		/* KEYPAD8 */
	{ .small = 0, .capital = 0 },		/* KEYPAD9 */
	{ .small = 0, .capital = 0 },		/* MINUS */
	{ .small = 0, .capital = 0 },		/* KEYPAD4 */
	{ .small = 0, .capital = 0 },		/* KEYPAD5 */
	{ .small = 0, .capital = 0 },		/* KEYPAD6 */
	{ .small = 0, .capital = 0 },		/* PLUS */
	{ .small = 0, .capital = 0 },		/* KEYPAD1 */
	{ .small = 0, .capital = 0 },		/* KEYPAD2 */
	{ .small = 0, .capital = 0 },		/* KEYPAD3 */
	{ .small = 0, .capital = 0 },		/* KEYPAD0 */
	{ .small = 0, .capital = 0 },		/* KEYPADPOINT */
	{ .small = 0, .capital = 0 },		/* IGNORE1 */
	{ .small = 0, .capital = 0 },		/* IGNORE2 */
	{ .small = 0, .capital = 0 },		/* IGNORE3 */
	{ .small = 0, .capital = 0 },		/* F11 */
	{ .small = 0, .capital = 0 },		/* F12 */
	{ .small = 0, .capital = 0 },		/* UNDEFINED */
};

#endif
