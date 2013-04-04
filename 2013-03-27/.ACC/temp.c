#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>

int main()
{
int in = open("tmp", O_RDONLY);
char c;
char buf[100];
int get_new_word = 1;
int j = 0;
while(read(in, &c, 1) == 1)
{
if(get_new_word == 1)
{
if(c >= 'A' && c <= 'Z')
{
buf[j++] = c;
get_new_word = 0;
continue;
}
}
else
{
if(c >= 'a' && c <= 'z')
{
buf[j++] = c;
continue;
}
if(c == ' ')
{
buf[j++] = ' ';
get_new_word = 1;
continue;
}
}
}
write(1, buf, strlen(buf));
close(in);
exit(0);
}
