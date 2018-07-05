#include <stdio.h>



int main(int argc, const char *argv[])
{
	char buf[128];
	gets(buf);

	char *p = buf;
	char *q = NULL;

	while(*p != '\0')
	{
		if(*p == ' ')
		{
			q = p;
			while(*q != '\0')
			{
				*q = *(q+1);
				q++;
			}
		}
		else
		{
			p++;
		}

	}
	puts(buf);

	return 0;
}
