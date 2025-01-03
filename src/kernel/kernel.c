void blank_screen(void)
{
	char *vidptr = (char*)0xb8000;	//video mem begins here.
	unsigned int i = 0;

	/* this loops clears the screen
	 * there are 25 lines each of 80 columns;
	 * each element takes 2 bytes */
	while(i < 80 * 25 * 2) {
		/* blank character */
		vidptr[i] = ' ';
		/* attribute-byte - light grey on black screen */
		vidptr[i+1] = 0x07; 		
		i += 2;
	}
}

void write_on_screen(char *str)
{
	char *vidptr = (char*)0xb8000;	//video mem begins here.

	unsigned int i = 0;
	unsigned int j = 0;

	/* this loop writes the string to video memory */
	while(str[j] != '\0') {
		/* the character's ascii */
		vidptr[i] = str[j];
		/* attribute-byte: give character black bg and light grey fg */
		vidptr[i+1] = 0x07;
		++j;
		i = i + 2;
	}
}

void main(void)
{
	char *str = "42 - rleseur";

	blank_screen();

	write_on_screen(str);

	return;
}
