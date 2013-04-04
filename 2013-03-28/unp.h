#ifndef UNP
#define UNP

#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include <string.h>

#include <fcntl.h>
#include <stdio.h>

int Socket(int domain, int type, int protocol)
{
	int fd = socket(domain, type, protocol);
	if(fd == -1)
	{
		perror("socket");
		exit(-1);
	}
	return fd;
}

int Bind(int sockfd, struct sockaddr *my_addr, int addrlen)
{
	int res = bind(sockfd, my_addr, addrlen);
	if(res == -1)
	{
		perror("bind");
		exit(-1);
	}
	return res;
}

int Connect(int sockfd, struct sockaddr *serv_addr, int addrlen)
{
	int res = connect(sockfd, serv_addr, addrlen);
	if(res == -1)
	{
		perror("connect");
		exit(-1);
	}
	return res;
}

int Accept(int sockfd, struct sockaddr *addr, int *addrlen)
{
	int cli_fd = accept(sockfd, addr, addrlen);
	if(cli_fd == -1)
	{
		perror("accept");
		exit(-1);
	}
	return cli_fd;
}

int Listen(int sockfd, int backlog)
{
	int res = listen(sockfd, backlog);
	if(res == -1)
	{
		perror("listen");
		exit(-1);
	}
	return res;
}

int Close(int fd)
{
	int res = close(fd);
	if(res == -1)
	{
		perror("close");
		exit(-1);
	}
	return res;
}

ssize_t Write(int fd, const void *buf, size_t count)
{
	ssize_t res = write(fd, buf, count);
	if(res == -1)
	{
		perror("write");
		exit(-1);
	}
	return res;
}

ssize_t Read(int fd, void *buf, size_t count)
{
	ssize_t res = read(fd, buf, count);
	if(res == -1)
	{
		perror("read");
		exit(-1);
	}
	return res;
}

/*
int Open(const char *pathname, int flags)
{
	int fp = open(pathname, flags);
	if(fp == -1)
	{
		perror("open");
		exit(-1);
	}
	return fp;
}
*/

int Open(const char *pathname, int flags, mode_t mode)
{
	int fp = open(pathname, flags, mode);
	if(fp == -1)
	{
		perror("open");
		exit(-1);
	}
	return fp;
}

#endif
