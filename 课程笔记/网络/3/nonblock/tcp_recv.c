#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/types.h>
#include<signal.h>
#include<stdlib.h>

#include<sys/fcntl.h>
#include<errno.h>

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
	char buf[10];

	int flag;
	while(1)
	{
		datafd = accept(sockfd,(struct sockaddr *)&cliaddr,&len);
		flag = fcntl(datafd,F_GETFL);
		flag |= O_NONBLOCK;
		fcntl(datafd,F_SETFL,flag);

		pid = fork();

		if(pid == -1)
		{
		
		}
		else if(pid == 0)
		{
			close(sockfd);	
			while(1)
			{
				n = recv(datafd,buf,sizeof(buf),0);
				if(n == -1)
				{
					if(errno == EAGAIN)
					{
						printf("有非阻塞\n");
						continue;
					}
					else 
					{
						perror("recv");
						exit(EXIT_FAILURE);
					}
				}
				if(n == 0)
				{
					printf("%s退出\n",inet_ntoa(cliaddr.sin_addr));
					exit(EXIT_SUCCESS);
				}
				if(n > 0)
				{
					printf("buf:%s\n",buf);	
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
