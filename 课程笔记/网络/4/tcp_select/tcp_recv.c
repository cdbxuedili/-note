#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/types.h>
#include<sys/select.h>

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

	socklen_t len = sizeof(cliaddr);

	int maxfd = sockfd;

	int ret;
	fd_set globalfds;
	FD_ZERO(&globalfds);
	FD_SET(sockfd,&globalfds);

	fd_set currentfds;
	int n;
	int i;
	char buf[10];
	while(1)//叫做tcp循环服务器模型,几乎不使用
	{
		FD_ZERO(&currentfds);
		currentfds = globalfds;
		ret = select(maxfd + 1,&currentfds,NULL,NULL,NULL);
		printf("ret = %d\n",ret);

		for(i = 3;i < maxfd + 1;i ++)
		{
			if(FD_ISSET(i,&currentfds))
			{
				if(i == sockfd)
				{
					datafd = accept(i,(struct sockaddr *)&cliaddr,&len);

					FD_SET(datafd,&globalfds);

					if(datafd > maxfd)
						maxfd = datafd;
				}
				else 
				{
					memset(buf,0,sizeof(buf));
					n = recv(i,buf,sizeof(buf),0);				

					if(n == -1)
						perror("recv");

					if(n == 0)
					{
						FD_CLR(i,&globalfds);
						close(i);

						if(i == maxfd)
						{
							while(--maxfd)
							{
								if(FD_ISSET(maxfd,&globalfds))
									break;
							}
						}
						printf("%s,%d退出\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
					}

					if(n > 0)
					{
						printf("ip:%s,port:%d,buf:%s\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port),buf);	
					}
				}
			}
		}


	}
	return 0;
}
