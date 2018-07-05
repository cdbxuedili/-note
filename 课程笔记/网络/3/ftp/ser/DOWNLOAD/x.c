#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/types.h>
#include<signal.h>
#include<stdlib.h>
#include<dirent.h>

#define LIST 1
#define DOWN 2

#define FALSE 3
typedef struct ftp_data
{
	int type;
	int flag;
	char data[128];
	char fname[15];
	size_t len;
}my_ftp_data_t;

void user_list(my_ftp_data_t info,int datafd)
{
	DIR *pdir;
	struct dirent *rp;

	memset(info.data,0,sizeof(info.data));
	pdir = opendir("./DOWNLOAD/");
	chdir("./DOWNLOAD/");
	
	while((rp = readdir(pdir)) != NULL)
	{
		if(rp->d_name[0] == '.')
			continue;
		
		strcat(info.data,rp->d_name);//1.txt
		info.data[strlen(info.data)] = ' ';//1.txt空格
	}
	send(datafd,&info,sizeof(info),0);
}

void user_down(my_ftp_data_t info,int datafd)
{
	char path[32];
	FILE *fp;

	sprintf(path,"./DOWNLOAD/%s",info.fname);//   ./DOWNLOAD/1.txt

	fp = fopen(path,"r");
	if(fp == NULL)
	{
		perror("fopen");
		info.flag = FALSE;
		send(datafd,&info,sizeof(info),0);
		exit(EXIT_FAILURE);
	}
	
	memset(info.data,0,sizeof(info.data));
	while(1)
	{
		info.len = fread(info.data,1,sizeof(info.data),fp);	

		send(datafd,&info,sizeof(info),0);
		if(info.len < sizeof(info.data))
			break;
	}
	fclose(fp);
}

int main(int argc, const char *argv[])
{
	int sockfd,datafd;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in seraddr,cliaddr;

	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(atoi(argv[1]));
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.194");


	if(bind(sockfd,(const struct sockaddr *)&seraddr,sizeof(seraddr)) == -1)
	{
		perror("bind");
		return -1;
	}

	if(listen(sockfd,5) == -1)
	{
		perror("listen");
		return -1;
	}

	signal(SIGCHLD,SIG_IGN);
	pid_t pid;
	socklen_t len = sizeof(cliaddr);
	ssize_t n;
	my_ftp_data_t info;
	while(1)
	{
		datafd = accept(sockfd,(struct sockaddr *)&cliaddr,&len);
		pid = fork();

		if(pid == -1)
		{
		
		}
		else if(pid == 0)
		{
			close(sockfd);	
			while(1)
			{
				n = recv(datafd,&info,sizeof(info),0);
				if(n == -1)
				{
					perror("recv");
					exit(EXIT_FAILURE);
				}
				if(n == 0)
				{
					printf("%s退出\n",inet_ntoa(cliaddr.sin_addr));
					exit(EXIT_SUCCESS);
				}

				switch(info.type)
				{
				case LIST:
					user_list(info,datafd);
					break;
				case DOWN:
					user_down(info,datafd);
					break;
				}
			}
		}
		else 
		{
			close(datafd);	
		}
	}
	return 0;
}
