#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	int sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	sockaddr_in srvaddr;
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //主机字节序转网络字节序
	srvaddr.sin_port = htons(1234);
	connect(sock, (sockaddr *)&srvaddr, sizeof(srvaddr));

	sleep(1); 
	char buffer[128] = {0};
	read(sock, buffer, sizeof(buffer)-1); //因为有缓冲区，出现粘包问题（没复现）
	printf("%s\n", buffer);

	//close(sock);
	
	return 0;
}
