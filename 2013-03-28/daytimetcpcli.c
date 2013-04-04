#include "unp.h"

int main( int argc, char *argv[])
{
	int sockfd, n;
	struct sockaddr_in server_addr;

	if(argc != 2)
	{
		write(2,"usage: daytimetcpcli <IPAddress>\n", 34);
		exit(-1);
	}
	
	sockfd = Socket(AF_INET, SOCK_STREAM, 0);

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9999);
	server_addr.sin_addr.s_addr = inet_addr(argv[1]);
	
	Connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr) );

	char buf[100];
	int len;
	int i=0;
	while( (len = Read(sockfd, buf, 13)) > 0)
	{
		i++;
		Write(1, buf, len);
	}
	
	Close(sockfd);
	exit(0);
}
