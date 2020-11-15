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
	if (0 != connect(sock, (sockaddr *)&srvaddr, sizeof(srvaddr)))
  {
    printf("connect error!\n");
    return -1;
  }

	char buffer[128] = {0};
  strncpy(buffer, "I'm comming", sizeof(buffer));
  if (-1 == write(sock, buffer, sizeof(buffer)))
  {
    printf("write error!\n");
  }
  memset(buffer, 0, sizeof(buffer));
	read(sock, buffer, sizeof(buffer)-1); 
	printf("%s\n", buffer);

	close(sock);
	
	return 0;
}
