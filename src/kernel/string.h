#ifndef STRING_H
# define STRING_H

char *itoa(int n);
void *memcpy(void *dest, const void *src, int n);
int strncmp(char *s1, char *s2, unsigned int n);
void printf(const char *str, int color, ...);

#endif
