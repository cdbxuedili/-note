#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>

int main(int argc, const char *argv[])
{
	int sockfd;

	sockfd = socket(AF_INET,SOCK_DGRAM,0);

	struct sockaddr_in multiaddr;
	multiaddr.sin_family = AF_INET;
	multiaddr.sin_port = htons(50000);
	multiaddr.sin_addr.s_addr = inet_addr("224.1.2.3");

	bind(sockfd,(struct sockaddr *)&multiaddr,sizeof(multiaddr));

	struct ip_mreqn addr;

	addr.imr_multiaddr.s_addr = inet_addr("224.1.2.3");
	addr.imr_address.s_addr = inet_addr("172.25.1.194");
	addr.imr_ifindex = 0;
	setsockopt(sockfd,IPPROTO_IP,IP_ADD_MEMBERSHIP,&addr,sizeof(addr));

	char buf[10];
	while(1)
	{
		recvfrom(sockfd,buf,sizeof(buf),0,NULL,NULL);
		printf("%s\n",buf);
	}

	return 0;
}
