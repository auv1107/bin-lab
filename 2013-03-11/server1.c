#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

#include <curses.h>


#define START_ROW 10
#define START_COL 20

void write_ch_to_screen(char *ch, int len)
{
	mvprintw(START_ROW, START_COL, ch);
	refresh();
}

int main()
{
	int server_sockfd, client_sockfd;
	int server_len, client_len;
	struct sockaddr_un server_address;
	struct sockaddr_un client_address;
	int len;
	char ch[1024];

	initscr();

	unlink("server_socket");
	server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
	
	server_address.sun_family = AF_UNIX;
	strcpy(server_address.sun_path, "server_socket");
	server_len = sizeof(server_address);
	bind(server_sockfd, (struct sockaddr *)&server_address, server_len);

	listen(server_sockfd, 5);
	while(1)
	{
		printf("server waiting\n");

		client_len = sizeof(client_address);
		client_sockfd = accept(server_sockfd, (struct sockaddr*)&client_address, &client_len);

		while(1)
		{
			len = read(client_sockfd, ch, 1024);
			write_ch_to_screen(ch, len);
			sleep(1);
		}
		close(client_sockfd);
	}

	endwin();
}
