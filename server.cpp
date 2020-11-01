#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

int main()
{
	int srvsock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	sockaddr_in srvaddr;
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sin_family = AF_INET;
	srvaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); //主机字节序转网络字节序
	srvaddr.sin_port = htons(1234);
	bind(srvsock, (sockaddr *)&srvaddr, sizeof(srvaddr));

	listen(srvsock, 5); //最大连接数5

	while (1)
	{
		sockaddr_in cltaddr;
		socklen_t cltaddrlen = sizeof(cltaddr);
		int cltsock = accept(srvsock, (sockaddr *)&cltaddr, &cltaddrlen);

		//新连接处理最笨的方法：创建线程
		char str[] = "您已上线";
		write(cltsock, str, sizeof(str));
		write(cltsock, str, sizeof(str));

		//close(cltsock);
	}

	close(srvsock);

	return 0;
}
