#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main()
  {
  
int pipefd[2];
pipe(pipefd);
int generator_pid, consumer_pid;
   
char *dumy[] = { NULL };

	if(!(generator_pid = fork()))
	{ 
	
	dup2(pipefd[1], 1);
	close(pipefd[1]);
	execve("./generator", dumy, dumy); 
	exit(0);
	}
	
sleep(1);
kill(generator_pid, SIGINT);

waitpid(generator_pid, NULL, WNOHANG); 
	   
	if (!(consumer_pid = fork()))
	{
	 
	dup2(pipefd[0], 0);
	close(pipefd[1]);
	execve("./consumer", dumy, dumy); 
	exit(0);
	   
	}
	
   return 0;
   
  }
