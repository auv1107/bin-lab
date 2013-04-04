#include "unp.h"

#include <time.h>

int main()
{
	int server_fd, client_fd;
	struct sockaddr_in server_addr, client_addr;
	int server_len, client_len;

	time_t ticks;
	char buf[100];

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(9999);
//	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_len = sizeof(server_addr);

	server_fd = Socket(AF_INET, SOCK_STREAM, 0);
	
	Bind(server_fd, (struct sockaddr*)&server_addr, server_len);

	Listen(server_fd, 5);

	for( ; ; )
	{
		client_fd = Accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
	
		ticks = time(NULL);
		snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks) );
		Write(client_fd, buf, strlen(buf) );

		Close(client_fd);
	}

	exit(0);
}

