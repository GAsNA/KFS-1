#include "kernel.h"
#include "keyboard_map.h"

/**
 * Allows to read a byte of the content of an input/output port
 *
 * Function from the sys/io.h file
 *
 * @param __port port on which data is read
 * @return char of data read
 */
static __inline unsigned char inb (unsigned short int __port)
{
	unsigned char _v;

	__asm__ __volatile__ ("inb %w1,%0":"=a" (_v):"Nd" (__port));
	return _v;
}

/**
 * Return true (1) if a byte is read from port 0x64
 *
 * @return true or false
 */
int is_key_available(void)
{
	return (inb(KEYBOARD_STATUS_PORT) & 1) == 1;
}

/**
 * If a byte is read on the keyboard port, process the information
 *
 * @return void
 */
void simulate_keyboard_interrupt(void)
{
	if (is_key_available())
		keyboard_handler();
}

/**
 * Get a keycode from the port 0x60 and print on console the associated char
 *
 * @return void
 */
void keyboard_handler(void) {
	unsigned char status;
	unsigned char keycode;

	t_key selected_key;
	char selected_char;

	int is_pressed = 1;

	/* write EOI */
	write_port(0x20, 0x20);

	keycode = read_port(KEYBOARD_DATA_PORT);

	/* Check if key is pressed or not */
	if (keycode >= 0x80)
		is_pressed = 0;
	if (!is_pressed)
		keycode -= 0x80;

	/* Check if keycode is valid and is shift */
	if (keycode < 0)
		return;
	if (keycode == LSHIFT || keycode == RSHIFT)
	{
		if (is_pressed)
			terminal.shift = 1;
		else
			terminal.shift = 0;
		return;
	}
		
	/* If key is not pressed, do not write on terminal and return */
	if (!is_pressed)
		return;
		
	/* Check the keycode for non-printable char */
	if (keycode == CAPSLOCK)
	{
		terminal.capslock = !terminal.capslock;
		return;
	}
	if (keycode == NUMSLOCK)
	{
		terminal.numslock = !terminal.numslock;
		return;
	}
	if (keycode == F1)
	{
		change_screen(terminal.current_screen - 1);
		return;
	}
	if (keycode == F2)
	{
		change_screen(terminal.current_screen + 1);
		return;
	}

	/* Selected the char given by inputs */
	selected_key = keyboard_map[keycode];

	if (terminal.numslock && selected_key.numslock != 0)
	{
		if (!terminal.shift)
			selected_char = selected_key.numslock;
		else
			return;
	}
	else if (terminal.capslock && selected_key.capital != 0)
	{
		if (terminal.shift)
			selected_char = selected_key.small;
		else
			selected_char = selected_key.capital;
	}
	else if (selected_key.small != 0)
	{
		if (terminal.shift)
			selected_char = selected_key.capital;
		else
			selected_char = selected_key.small;
	}
	else
		return;

	/* Write on terminal the selected char */
	print_char_on_console(selected_char, LIGHT_GRAY);
}
