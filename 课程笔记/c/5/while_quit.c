#include <stdio.h>



int main(int argc, const char *argv[])
{
	int ch;
	while(1)
	{
		ch = getchar();
		if(ch == 'q')
		{
			break;
		}
		putchar(ch);
	
	}
	return 0;
}
