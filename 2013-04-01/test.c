#include<unistd.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/wait.h>
main()
{
pid_t pid;
int status;
if(!(pid= fork())){
	printf("Hi I am child process!\n");
	sleep(10);
	return;
}
else{
	printf("send signal to child process (%d) \n",pid);
	sleep(3);
	kill(pid,SIGABRT);
	wait(&status);
if(WIFSIGNALED(status))
printf("chile process receive signal %d\n",WTERMSIG(status));
}
}
