#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<sys/types.h>
#include<sys/epoll.h>

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

	int epfd;
	epfd = epoll_create(100);
	
	struct epoll_event ev;

	//理解为FD_SET();
	ev.events = EPOLLIN;//确定监控的事件是读事件
	ev.data.fd = sockfd;//监控的文件描述符
	epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&ev);//为了监控sockfd

	int ret;
	struct epoll_event readyev[100];//存放了就绪的文件描述符

	int i;
	int n;
	char buf[10];
	while(1)
	{
		ret = epoll_wait(epfd,readyev,100,-1);
		printf("ret = %d\n",ret);

		for(i = 0;i < ret;i ++)
		{
			if(readyev[i].data.fd == sockfd)
			{
				datafd = accept(sockfd,(struct sockaddr *)&cliaddr,&len);

				ev.events = EPOLLIN;
				ev.data.fd = datafd;
				epoll_ctl(epfd,EPOLL_CTL_ADD,datafd,&ev);//将datafd将入到监控表中
			}
			else 
			{
				memset(buf,0,sizeof(buf));
				n = recv(readyev[i].data.fd,buf,sizeof(buf),0);	
				if(n == -1)
					perror("recv");

				if(n == 0)
				{
					epoll_ctl(epfd,EPOLL_CTL_DEL,readyev[i].data.fd,NULL);	
					close(readyev[i].data.fd);
					printf("有客户端退出\n");
				}
				if(n > 0)
					printf("ip:%s,buf:%s\n",inet_ntoa(cliaddr.sin_addr),buf);
			}
		}
	}
	return 0;
}
