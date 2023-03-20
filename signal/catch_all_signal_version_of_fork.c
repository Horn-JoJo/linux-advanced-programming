#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>

void handler(int sig) {
	printf("\n%s: sig: %d\n", __func__, sig);
	if (SIGCHLD == sig){
		wait(NULL);
	}
}

int main() {

	int i;
	for (i = 1; i <= 64; i++) {
		if (SIG_ERR == signal(i, handler)){
			printf("sig: %d:%s\n", i, strerror(errno));
		}
	}

	pid_t pid;
	pid = fork();
	if (0 > pid) {
		perror("fork");
		return -1;
	}else if (0 == pid) {
		while(1){
			printf("son process suspend");
			pause();
		}
	}else{
#define MAX 36
		char buf[MAX];
		while(1) {
			printf("Please input signum:\n");
			fgets(buf, MAX, stdin);
			int len = strlen(buf);
			buf[len - 1] = 0;

			int signum = atoi(buf);
			if(0 > kill(pid, signum)) {
				perror("signal");
			}
		}
	}
	return 0;
}
