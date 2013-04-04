#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <string.h>

void put_file(char *buf, int client_fd, int len);
int isexist(char *buf);

int main()
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);
	if(server_fd < 0)
	{
		perror("socket");
		exit(-1);
	}

	int client_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	int server_len, client_len;
	int len;

	char buf[1024] = "welcome to my server\n";
	char ret;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8000);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_len = sizeof(server_addr);
	int res = bind(server_fd, (struct sockaddr*)&server_addr, server_len);
	if(res == -1)
	{
		perror("bind");
		exit(-1);
	}
	

	listen(server_fd, 5);
	write(1, "listening....\n", 14);

	while(1)
	{
		client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
		write(client_fd, buf, strlen(buf) );
		len = read(client_fd, buf, 1024);
		if(isexist(buf))
		{
			ret = 'y';
			write(client_fd, &ret, 1);
			put_file(buf, client_fd, len);
		}
		else
		{
			ret = 'n';
			write(client_fd, &ret, 1);
			close(client_fd);
			break;
		}
	}

	close(server_fd);
	exit(0);
}


void put_file(char *buf, int client_fd, int len)
{
	char filename[100] = "makefile";
	memcpy(filename, buf, len-1);
	int in = open(filename, O_RDONLY);
	if(in < 0)
	{
		perror("open");
		exit(-2);
	}

	while((len = read(in, buf, 1024)) != 0)
		write(client_fd, buf, len);
		
	close(in);
}

int isexist(char *buf)
{
	return 1;
}
