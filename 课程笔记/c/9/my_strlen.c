#include <stdio.h>

int my_strlen(const char *s);

int main(int argc, const char *argv[])
{
	char buf[128];
	gets(buf);
	printf("%d\n",my_strlen(buf));
	return 0;
}

int my_strlen(const char *s)
{
	int len = 0;
	while(*s != '\0')
	{
		len++;
		s++;
	}
	return len;
}
