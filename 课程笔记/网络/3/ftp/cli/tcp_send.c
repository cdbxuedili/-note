#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include"head.h"
#include"head.h"


#if 0
#define LIST 1
#define DOWN 2
#define FALSE 3
#define TRUE 4
typedef struct ftp_data
{
	int type;
	int flag;
	char data[128];
	char fname[15];
	size_t len;
}my_ftp_data_t;
#endif
void user_list(my_ftp_data_t info,int sockfd)
{
	int i;
	int count = 0;
	info.type = LIST;
	send(sockfd,&info,sizeof(info),0);
	recv(sockfd,&info,sizeof(info),0);
//	printf("%s\n",info.data);
	
	for(i = 0;i < strlen(info.data);i ++)
	{
		printf("%c",info.data[i]);

		if(info.data[i] == ' ')
		{
			count ++;
			if(count % 2 == 0)
				printf("\n");
		}
	}
	printf("\n");

}

void user_down(my_ftp_data_t info,int sockfd)
{
	FILE *fp;
	printf("请输入要下载的文件名:");
	fgets(info.fname,sizeof(info.fname),stdin);
	info.fname[strlen(info.fname) - 1] = '\0';
	
	info.type = DOWN;
	send(sockfd,&info,sizeof(info),0);
	recv(sockfd,&info,sizeof(info),0);

	if(info.flag == FALSE)
	{
		printf("文件打开失败\n");
		exit(EXIT_FAILURE);
	}

	if(info.flag == TRUE)
	{
		printf("文件打开成功\n");
	}
	
	fp = fopen(info.fname,"w");
	while(1)
	{
		recv(sockfd,&info,sizeof(info),0);	
		fwrite(info.data,1,info.len,fp);
		if(info.len < sizeof(info.data))
			break;
	}
	printf("文件下载成功\n");
	fclose(fp);
}

int main(int argc, const char *argv[])
{
	int sockfd;

	sockfd = socket(AF_INET,SOCK_STREAM,0);

	struct sockaddr_in seraddr;
	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(atoi(argv[1]));
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.194");

	if(connect(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr)) == -1)
	{
		perror("connect");
		return -1;
	}
	
	char buf[10];
	int choose;

	my_ftp_data_t info;
	while(1)
	{
		printf("**********1. list **********\n");
		printf("**********2. down **********\n");
		
		fgets(buf,sizeof(buf),stdin);
		choose = buf[0] - '0';

		switch(choose)
		{
		case 1:
			user_list(info,sockfd);
			break;
		case 2:
			user_down(info,sockfd);
			break;
		}
	}
	return 0;
}
