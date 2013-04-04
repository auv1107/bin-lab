#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main()
{
	char dir[] = "hello world,";
	char ch[] = ",";
	if(strstr(dir, ch))
	{
		printf("yes\n");
	}
	else
		printf("no\n");
	
	return 0;
}
