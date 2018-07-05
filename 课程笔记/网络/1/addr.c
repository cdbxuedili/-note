#include<stdio.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

int main(int argc, const char *argv[])
{
	in_addr_t naddr;

	naddr = inet_addr("192.168.1.2");
	printf("%x\n",naddr);

	struct in_addr in;
	in.s_addr = naddr;
	char *ip;
	ip = inet_ntoa(in);
	printf("%s\n",ip);
	return 0;
}
