#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

struct stat * buf;
int fun(char * name);


int main(int argc, const char *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr,"please input path!\n");
		return -1;
	}

	DIR *dir = NULL;
	struct dirent * rd;
	buf = malloc(sizeof(struct stat));

	dir = opendir(argv[1]);
	if(dir == NULL)
	{
		perror("fail to opendir");
		return -1;
	}

	while(1)
	{
	rd = readdir(dir); //读取文件信息
	if(rd == NULL)
	{
		if(errno == 0)
		{
			break;
		}
		else
		{
			perror("fail to readdir");
			return -1;
		}
	}
	fun(rd->d_name);//传递文件名

	}

	closedir(dir);


	return 0;
}

int fun(char * name)
{
	stat(name,buf);
	
	switch(buf->st_mode & S_IFMT)
	{
		case S_IFBLK:
			printf("b");
			break;
		case S_IFCHR:
			printf("c");
			break;
		case S_IFDIR:
			printf("d");
			break;
		case S_IFIFO:
			printf("p");
			break;
		case S_IFLNK:
			printf("l");
			break;
		case S_IFREG:
			printf("-");
			break;
		case S_IFSOCK:
			printf("s");
			break;
		default:
			printf("?");
			break;
	}
	
	printf("size:%ld,name:%s\n",buf->st_size,name);


}



