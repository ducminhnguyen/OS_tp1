#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

pid_t ret;

void signal_handler(int signum) 
{
	if (ret != 0 && ret != -1)
  {
		printf("Parent will now exit\n");
		kill(ret, SIGKILL);
	}
}

void my_sigchld_handler(int sig)
{
    pid_t p;
    int status;

    while ((p=waitpid(-1, &status, WNOHANG)) != -1)
    {
       printf("Kill child success\n");
    }
}

struct sigaction sa;

/*int main(void) {
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = my_sigchld_handler;

	sigaction(SIGCHLD, &sa, NULL);
  
	char *name;
	signal(SIGTERM, signal_handler);
	signal(SIGINT, signal_handler);
  ret = fork();  

  if (ret == 0) { /* Child /
    name = "child";
		printf("Before sleep");
    sleep(20);
  } else if (ret == -1) {
    printf("Cannot create process");
    return -1;
  } else {
    name = "parent";
		
    sleep(10);
  }

//  name[1] = 'o';

  printf("process %s ret  = %ld\n", name, ret);
  return 0;
}*/

int main()
{
	pid_t* childProcessArr;
	childProcessArr= (pid_t*)malloc(sizeof(pid_t)*3);
	int isRoot = 1;
	printf("Parent\n");
	int i = 0;
	for (i = 0; i< 3; ++i) 
	{
			childProcessArr[i] = fork();
			if (childProcessArr[i] == 0)
			{
				isRoot = 0;
				break;
			} 
			else
			{
				printf("process %s ret  = %ld\n", "child", childProcessArr[i]);
			}
	}
	if (isRoot == 1 || i == 1) {sleep(200);return 0;}
	pid_t* childChildProcessArr = (pid_t*)malloc(sizeof(pid_t)*2);
	for (i = 0; i< 2; ++i) 
	{
			childChildProcessArr[i] = fork();
			if (childChildProcessArr[i] == 0)
			{
				printf("In Child CHild");
				break;
			}
			else 
			{
				printf("process %s ret  = %ld\n", "grandchild", childChildProcessArr[i]);
			}
	}
	sleep(200);	
	return 0;
}

