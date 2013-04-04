#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#include <curses.h>

#include <signal.h>

#define LINES 40
#define COLS 140

int def_rate = 1;
int def_lines = LINES;
int def_cols = COLS;

struct Profile;
int create_socket(int);
void clean_program();
void get_Profile(struct Profile*);
char* get_one_line_of_pic();

struct Profile
{
	int lines;
	int cols;
};

void main()
{
	int sockfd = -1;
	printf("sockfd: %d", sockfd);
	struct Profile profile = {
		.lines = LINES,
		.cols = COLS
		};
	char *one_line_of_pic;
	int current_line = 0;

	printf("sockfd: %d", sockfd);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("sockfd: %d", sockfd);
//	(*signal(SIGINT, clean_program))(sockfd);

	create_socket(sockfd);

	get_Profile(&profile);

	write(sockfd, (char*)&profile, sizeof(profile));

	while(one_line_of_pic = get_one_line_of_pic())
	{
		write(sockfd, one_line_of_pic, COLS);

		if(++current_line == LINES)
		{
			sleep(1);
			current_line = 0;
		}
	}

	clean_program(sockfd);
	exit(0);
}


void clean_program(int sockfd)
{
	close(sockfd);
	exit(1);
}

int create_socket(int sockfd)
{
	struct sockaddr_in address;
//	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(9734);
	
	int len = sizeof(address);
	int result = connect(sockfd, (struct sockaddr*)&address, len);

	return result;
}

void get_Profile(struct Profile *profile)
{
	profile->lines = LINES;
	profile->cols = COLS;
}

char* get_one_line_of_pic()
{
	return NULL;
}
