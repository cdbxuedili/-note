#include <stdio.h>

char *my_strcat(char *dest,const char *src);

int main(int argc, const char *argv[])
{
	char dest[128];
	char src[128];
	char *s = NULL;
	gets(dest);
	gets(src);
	s = my_strcat(dest,src);
	puts(s);
	return 0;
}

char *my_strcat(char *dest,const char *src)
{
	char *address = dest;
	while(*dest)
	{
		dest++;
	}
	while(*src)
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return address;
}


