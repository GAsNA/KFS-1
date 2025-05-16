#ifndef STRING_H
# define STRING_H

char *itoa(int n);
void *memcpy(void *dest, const void *src, int n);
int strncmp(char *s1, char *s2, unsigned int n);
void putaddr(int num, int colour);
void puthexa_small(int nb, int colour);
void puthexa_capital(int nb, int colour);

#endif
