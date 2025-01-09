#ifndef KEYBOARD_H
# define KEYBOARD_H

extern char	read_port(unsigned short port);
extern void	write_port(unsigned short port, unsigned char data);
extern void	load_idt(long unsigned int* idt_address);
extern void	keyboard_handler();

# define KEYBOARD_DATA_PORT 0x60
# define KEYBOARD_STATUS_PORT 0x64

int is_key_available();
void simulate_kb_interrupt();

void keyboard_handler_main(void);

#endif
