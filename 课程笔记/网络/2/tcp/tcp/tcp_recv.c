#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/types.h>

int main(int argc, const char *argv[])
{
	int sockfd,datafd;

	sockfd = socket(AF_INET,SOCK_STREAM,0);
	if(sockfd == -1)
	{
		perror("socket");
		return -1;
	}

	struct sockaddr_in seraddr;

	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(atoi(argv[1]));
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.194");

//	int on = 1;
//	setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));

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

	socklen_t len = sizeof(seraddr);
	while(1)//叫做tcp循环服务器模型,几乎不使用
	{
		printf("1\n");
		datafd = accept(sockfd,(struct sockaddr *)&seraddr,&len);	
		printf("2\n");
		if(datafd == -1)
		{
			perror("accept");
			return -1;
		}

		ssize_t n;
		char buf[10];
		while(1)
		{
			memset(buf,0,sizeof(buf));
			n = recv(datafd,buf,sizeof(buf),0);
			if(n == -1)
			{
				perror("recv");
				return -1;
			}

			if(n == 0)
			{
				printf("有客户端退出\n");
				break;
			}
			if(n > 0)
			{
				printf("%s\n",buf);
			}
		}
	}
	return 0;
}
