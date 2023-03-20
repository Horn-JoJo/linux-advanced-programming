#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<signal.h>
#include<pthread.h>

void handler(int sig) {
	printf("sig = %d\n", sig);
	wait(NULL);
}

int main(){
	
	pid_t pid;	
	pid = fork();
	signal(SIGCHLD, handler);
	if (0 > pid) {
		perror("fork");
		return -1;
	}else if (0 == pid){
		printf("son process exit.\n");
	}else {
		printf("father process:%d\n", getpid());
		
		pause();
		int i = 5;
		while(i) {
			sleep(1);
			printf("%d s.\n", i--);
		}
		printf("father process exit.\n");
	}

	return 0;
}
