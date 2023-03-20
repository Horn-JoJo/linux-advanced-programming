#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>

void deal_corpse(int sig)
{
	int status;
	wait(&status);
	printf("return val:%d\n", WEXITSTATUS(status));
}

int main()
{
	signal(SIGCHLD, deal_corpse);

	pid_t pid = fork();
	if (0 > pid)
	{
		perror("fork");
		return -1;
	}
	else if (0 == pid)
	{
		printf("son process:%d\n", getpid());
		sleep(1);
		return 11;
	}
	else 
	{
		printf("father process start.\n");
		sleep(3);
		printf("father process end.\n");
	}


	return 0;
}
