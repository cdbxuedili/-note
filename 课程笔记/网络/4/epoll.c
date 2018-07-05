#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/select.h>
#include <sys/epoll.h>



#define SA struct sockaddr

int main(int argc, const char *argv[])
{
	//socket
	int sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("fail to socket");
		exit(1);

	}

	struct sockaddr_in myaddr,peeraddr;
	myaddr.sin_family=AF_INET;
	myaddr.sin_port=htons(50000);
	myaddr.sin_addr.s_addr=inet_addr("0.0.0.0");

	socklen_t len=sizeof(peeraddr);

	char buf[128];
	int confd;

	//bind 
	int ret_bind=bind(sockfd,(SA*)&myaddr,sizeof(myaddr));
	if(ret_bind<0)
	{
		perror("fail to bind");
		exit(1);
	}

	int ret_lis=listen(sockfd,5);
	if(ret_lis<0)
	{
		perror("fail to listen ");
		exit(1);
	}

	// man 7 epoll 
	//select 问题
	//（1） 反复进行用户空间和内核空间的数据交换  （填充表）
	//（2） 无意义的遍历  （i<= maxfd）
	
	//epoll  一次添加文件描述符，不需要再添加了
	//就绪的结果将返回到一个数组中，不需要遍历 
	
	//select 缺点 恰好正是 epoll 的优点
	
	// 适合边缘触发和条件触发的  
	// 适合监控 大量的文件描述符 

	//epoll_create  创建epoll instance 返回文件描述符  -->open  creat 
	//关心的文件描述符  通过 epoll_ctl 来注册（删除）  --> FD_SET  FD_CLR
	//epoll_wait 监测等待文件描述符就绪     ---> select
	//
	
	//epoll_create
	int epfd=epoll_create(50);	
	//  size   是一个hint  不够的时候内核自己看着办
	//  骗人的：  新内核可以，就内核要出错的！！！！！！！
	//
	//  uname -a  3.13  旧内核特性不支持hint
	//  旧内核不够，多写点
	if(epfd<0)
	{
		perror("fail to epoll create");
		exit(1);
	
	}


	//epoll_ctl
	//1. epoll的fd
	//2. 操作的宏
	//3. 要操作的文件描述符
	//4.文件描述符对应的操作结构体
#if 0
  typedef union epoll_data {
	       void	   *ptr;
	       int	    fd;
	       uint32_t     u32;
	       uint64_t     u64;
	   } epoll_data_t;

	   struct epoll_event {
	       uint32_t     events;	 /* Epoll events */
	       epoll_data_t data;	 /* User data variable */
	   };

#endif
	   struct epoll_event ev;
	   ev.events=EPOLLIN;//读资源相关
	   ev.data.fd=0;
	   if(-1==epoll_ctl(epfd,EPOLL_CTL_ADD,0,&ev))
	   {
		   perror("fail to add 0");
		   exit(1);


	   }


	   ev.events=EPOLLIN;//读资源相关
	   ev.data.fd=sockfd;
	   if(-1==epoll_ctl(epfd,EPOLL_CTL_ADD,sockfd,&ev))
	   {
		   perror("fail to add sockfd");
		   exit(1);


	   }


		struct epoll_event events[50];

	   while(1)
	   {
			//epoll_wait
			// 1. epfd
			// 2. 返回就绪结果的数组名    struct epoll_event [];
			// 3. 数组元素的个数
			// 4. 超时信息   -1 不超时
			// 返回值  就绪的文件描述符的个数
			
		   int nfds=epoll_wait(epfd,events,50,-1);
		   if(nfds<0)
		   {
			   perror("fail to epoll wait");
			   exit(1);
		   
		   
		   }
		   else  //有就绪    按照顺序 将就绪结果的文件描述符  放入到events[0]  ~  events[ndfs-1] 里面
		   {
			   	int i;
				for(i=0;i<nfds;i++)
				{
					if(events[i].data.fd==0)//对每一个数组元素询问 是哪一种类型的io文件描述符 排他
					{
						bzero(buf,sizeof(buf));
						fgets(buf,sizeof(buf),stdin);
						printf("fgets:%s\n",buf);
					
					}
					else if(events[i].data.fd==sockfd)
					{
						confd=accept(sockfd,(SA*)&peeraddr,&len);
						if(confd<0)
						{
							perror("fail to accept");
							exit(1);

						}
						printf("peer ip:%s ,port:%d fd=%dis connected!\n",inet_ntoa(peeraddr.sin_addr),ntohs(peeraddr.sin_port),confd);

						ev.events=EPOLLIN;//读资源相关
						ev.data.fd=confd;
						if(-1==epoll_ctl(epfd,EPOLL_CTL_ADD,confd,&ev))
						{
							perror("fail to add confd");
							exit(1);


						}




					}
					else
					{
						bzero(buf,sizeof(buf));
						int ret_recv=recv(events[i].data.fd,buf,sizeof(buf),0);
						if(ret_recv<0)
						{
							perror("fail to recv");
							exit(1);
						
						
						}
						else if(ret_recv==0)
						{
							//先删除文件描述符，再关闭
							//epoll里面 存放的是打开着的文件描述符 
							//如果先关再删 会出错
							
							if(-1==epoll_ctl(epfd,EPOLL_CTL_DEL,events[i].data.fd,NULL))
							{
								perror("fail to del fd");
								exit(1);
							}

							close(events[i].data.fd);





						}
						else
						{
							printf("recv:%s\n",buf);

							send(events[i].data.fd,buf,strlen(buf),0);



						}



					}



				}



		   }







	   }

	   return 0;
}



