/* 操作程序参数的函数 getopt
	用法: getopt(int argc, char* argv[], char *optstring);
			extern char *optarg;
			extern int optind, opterr, optopt;

	实例: getopt(	argc,		argv,		":if:lr")
		如果选项有一个关联直， 则外部变量optarg 只想这个值
		如果选项处理完毕，返回-1  --回事getopt停止扫描选项
		无法识别的选项返回 '?', 该选项保存在optopt
		如果一个选项要求有一个关联值，而用户没有提供, 则返回'?'  若选项字符串以':' 开头， 则返回':'
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int opt;
	
	while((opt = getopt(argc, argv, ":if:lr")) != -1)
	{
		switch(opt)
		{
			case 'i':
			case 'l':
			case 'r':
				printf("option: %c\n", opt);
				break;
			case 'f':
				printf("filename: %s\n", optarg);
				break;
			case ':':
				printf("option needs a value\n");
				break;
			case '?':
				printf("unknown option: %c\n", optopt);
				break;
		}
	}

	for(opt=optind; opt < argc; opt++)
	{
		printf("argument: %s\n", argv[opt]);
	}
	
	exit(0);
}
