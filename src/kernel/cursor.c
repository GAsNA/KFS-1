#include "kernel.h"

/**
 * Moves the cursor of the framebuffer to the given position
 *
 * @param pos The new position of the cursor
 * @return void
 */
void move_cursor(unsigned int pos)
{
	if (pos % BYTES_FOR_ELEMENT != 0)
		return;

	// Move terminal cursor
	terminal.cursor = pos;

	// Move blinking cursor
	pos /= BYTES_FOR_ELEMENT;

    outb(COMMAND_PORT, HIGH_BYTE_COMMAND);
    outb(DATA_PORT,    ((pos >> 8) & 0x00FF));
    outb(COMMAND_PORT, LOW_BYTE_COMMAND);
    outb(DATA_PORT,    pos & 0x00FF);
}
