#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<signal.h>
#include<string.h>

void handler(int sig) {
	printf("%s : %d\n", __func__, sig);
}

int main(){
	
	int fd[2];
	if (0 > pipe(fd)) {
		perror("pipe");
		return -1;
	}

	signal(SIGPIPE, handler);
	pid_t pid;
	pid = fork();

	if(0 > pid) {
		perror("fork");
	}else if (0 == pid) {
		close(fd[0]);
		close(fd[1]);
	}else {
		close(fd[0]);
		
#define MAX 36
		char buf[MAX];
		sleep(1);
		printf("please input a str:\n");
		fgets(buf, MAX, stdin);
		int len  = strlen(buf);
		buf[len - 1] = 0;
		if (len != write(fd[1], buf, len)) {
			perror("write");
			close(fd[1]);
		}else {
			printf("write %d bytes:%s\n", len, buf);
		}
	}
	printf("pid:%d over!!!\n", getpid());
	return 0;
}
