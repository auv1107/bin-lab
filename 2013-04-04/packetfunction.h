#ifndef PACKETFUNCTION
#define PACKETFUNCTION _


#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>

int Open(const char* pathname, int flags)
{
	int fd = open(pathname, flags);
	if( fd == -1 )
	{
		perror("open");
		exit(-1);
	}
	return fd;
}

int Close(int fd)
{
	int res = close(fd);
	if ( res == -1 )
	{
		perror("close");
		exit(-1);
	}
	return res;
}

off_t Lseek(int fd, off_t offset, int whence)
{	
	off_t of = lseek (fd, offset, whence);
	if ( of == -1 )
	{
		perror("lseek");
		exit(-1);
	}
	return of;
}

ssize_t Read ( int fd, void *buf, size_t count )
{
	ssize_t len = read ( fd, buf, count );
	if ( len == -1 )
	{
		perror ("read");
		exit (-1);
	}
	return len;
}

ssize_t Write ( int fd, const void *buf, size_t count )
{
	ssize_t len = write ( fd, buf, count );
	if ( len == -1 )
	{
		perror("write");
		exit (-1);
	}
	return len;
}









#endif
