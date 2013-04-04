/*  char *getenv(const char *name);
	int putenv(const char *string);
	string: var=value
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if(argc == 1 || argc > 3)
	{
		fprintf(stderr, "usage: environ var [value]\n");
		exit(1);
	}

	char *var;
	char *value;

	var = argv[1];
	value = getenv(var);

	if(value)
	{
		printf("%s = %s\n", var, value);
	}
	else
	{
		printf("%s has no value\n", var);
	}

	if(argc == 3)
	{
		char *str;
		value = argv[2];
		str = malloc(strlen(var) + strlen(value) + 2);
		if(!str)
		{
			fprintf(stderr, "out of memory\n");
		}
		strcpy(str, argv[1]);
		strcat(str, "=");
		strcat(str, argv[2]);

		if(putenv(str) != 0)
		{
			fprintf(stderr, "putenv failed\n");
			free(str);
			exit(1);
		}
		value = getenv(var);
		printf("%s = %s\n", var, value);
	}

	exit(0);
}
