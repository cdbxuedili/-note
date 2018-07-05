#include <stdio.h>
#include <stdlib.h>



int main(int argc, const char *argv[])
{
#if 0
    void *malloc(size_t size);
	功能:在堆区空间上开辟size大小的一片连续的空间,且返回该连续空间的首地址
	参数:size_t == unsigned int   需要开辟的空间的大小
	返回值:返回该空间的首地址;
 	#include <stdlib.h>
#endif
	int *p = NULL;
	p = (int *)malloc(sizeof(int)*10);
	int i;
	for(i = 0;i < 10;i++)
	{
		*(p+i) = i*10;
	}
	
	for(i = 0;i < 10;i++)
	{
		printf("%d\n",*(p+i));
	}
#if 0
    void free(void *ptr);
	功能:释放以void *ptr为首地址的一片连续的空间
#endif
	free(p);
	return 0;
}
