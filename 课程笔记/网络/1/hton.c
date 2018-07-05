#include<stdio.h>
#include<arpa/inet.h>

int main(int argc, const char *argv[])
{
	uint32_t horder = 0x12345678;
	uint32_t norder;

	//涉及到端口号的字节序转化时使用
	norder = htonl(horder);//将主机字节序转化为网络字节序
	printf("%#x\n",norder);

	horder = ntohl(norder);//将网络字节序转化为主机字节序
	printf("%#x\n",horder);
	return 0;
}
