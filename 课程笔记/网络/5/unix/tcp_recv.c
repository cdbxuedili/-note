#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netinet/ip.h> /* superset of previous */
#include<stdlib.h>
#include<string.h>
#include<sys/un.h>

int main(int argc, const char *argv[])
{
	int sockfd;//监听套接字
	int connfd;//连接套接字

	if((sockfd = socket(AF_UNIX,SOCK_STREAM,0)) == -1)
	{
		perror("socket");
		exit(1);
	}

	char buf[64];
	struct sockaddr_un seraddr,cliaddr;
	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sun_family = AF_UNIX;
	strcpy(seraddr.sun_path,"./s");//域套接字文件名

	int ser_len = sizeof(seraddr.sun_family) + strlen(seraddr.sun_path);
	if(bind(sockfd,(struct sockaddr *)&seraddr,ser_len) == -1)
	{
		perror("bind");
		exit(1);
	}
	
	if(listen(sockfd,5) == -1)
	{
		perror("listen");
		exit(1);
	}
	int cli_len = sizeof(cliaddr.sun_family) + strlen(cliaddr.sun_path);
	if((connfd = accept(sockfd,(struct sockaddr *)&cliaddr,&cli_len)) == -1)
	{
		perror("accept");
		exit(1);
	}
	int n;
	while(1)
	{
		memset(buf,0,sizeof(buf));
		if((n = recv(connfd,buf,sizeof(buf),0)) == -1)
		{
			perror("recv");
			exit(1);
		}
		printf("n = %d,buf:%s\n",n,buf);

		send(connfd,buf,n,0);
	}

	close(sockfd);
	close(connfd);
	return 0;
}
