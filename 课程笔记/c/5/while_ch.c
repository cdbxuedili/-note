#include <stdio.h>



int main(int argc, const char *argv[])
{
	char ch = 0;
	int space = 0,other = 0,math = 0,word = 0;
	while(1)
	{
		scanf("%c",&ch);
		if(ch == '\n')
		{
			break;
		}

		if(ch == ' ')
		{
			space++;
		}
		else if(ch >= '0'&& ch <= '9')
		{
			math++;
		}
		else if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		{
			word++;
		}			
		else
		{
			other++;
		}

	}
		printf("输入字符空格%d个,数字字符%d个,字母%d个,其他字符%d个\n",space,math,word,other);


	
	return 0;
}
