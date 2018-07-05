#include<stdio.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/select.h>
#include<string.h>

int main(int argc, const char *argv[])
{
	int sockfd;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	struct sockaddr_in seraddr,cliaddr;

	memset(&seraddr,0,sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(atoi(argv[1]));
	seraddr.sin_addr.s_addr = inet_addr("172.25.1.194");

	bind(sockfd,(struct sockaddr *)&seraddr,sizeof(seraddr));

	int maxfd = sockfd;
	fd_set readfds;//代表了读表
	FD_ZERO(&readfds);
	int ret;

	int i;
	char buf[10];
	char buff[10];
	int n;
	socklen_t len = sizeof(cliaddr);
	while(1)
	{
		FD_SET(sockfd,&readfds);
		FD_SET(0,&readfds);
		ret = select(maxfd + 1,&readfds,NULL,NULL,NULL);
		printf("ret = %d\n",ret);

		for(i = 0;i <= maxfd;i ++)//暂时不知道哪个文件描述符就绪
		{
			if(FD_ISSET(i,&readfds))
			{
				if(i == 0)
				{
					memset(buf,0,sizeof(buf));
					read(i,buf,sizeof(buf));	
					printf("stdin:%s\n",buf);
				}

				if(i == sockfd)
				{
					memset(buff,0,sizeof(buff));
					n = recvfrom(i,buff,sizeof(buff),0,(struct sockaddr *)&cliaddr,&len);

					printf("ip:%s,port:%d,buff:%s\n",inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port),buff);
				}
			}
		
		}


	}
	return 0;
}
