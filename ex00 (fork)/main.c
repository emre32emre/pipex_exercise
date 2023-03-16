#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
	int pid = fork();

	if (pid > 0)
	{
		//wait(NULL);
		// parent proses
		printf("I'm parent my pid :%d my parent pid :%d\n",pid,getpid());
		
	}
	else if (pid == 0)
	{
		//child proses
		printf("I'm child my pid:%d my parent pid :%d\n",pid, getpid());
		
	}
	else 
	{
		//error
	}
}