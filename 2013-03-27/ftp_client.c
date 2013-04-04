#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <string.h>

void get_file(char *buf, int fd, int len);

int main()
{
	int fd = socket(AF_INET, SOCK_STREAM, 0);
	struct sockaddr_in server_addr;

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(8000);
	server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	int len = sizeof(server_addr);

	int res = connect(fd, (struct sockaddr*)&server_addr, len);
	if(res < 0)
	{
		perror("connect");
		exit(-1);
	}

	char buf[1024];
	len = read(fd, buf, 1024);
	write(1, buf, len);
	char ret;

	while(strcmp(buf, "quit") != 0)
	{
		len = read(0, buf, 1024);
		write(fd, buf, len);
		len = read(fd, &ret, 1);
		if(len == 1 && ret == 'y')
			get_file(buf, fd, len);
	}

	close(fd);
	exit(0);
}

void get_file(char *buf, int fd, int len)
{
	char filename[100] ;
	memcpy(filename, buf, len);
	int out = open(filename, O_WRONLY | O_CREAT , 0666);
	if(out < 0)
	{
		perror("open");
		exit(-1);
	}

	while((len = read(fd, buf, 1024)) != 0)
		write(out, buf, len);
	close(out);
}
