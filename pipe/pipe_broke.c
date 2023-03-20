#include<stdio.h>
#include<string.h>
#include<unistd.h>

int main(){
	pid_t pid;
	pid = fork();

	int fd[2];

	if(0 > pipe(fd)){
		perror("pipe");
		return -1;
	}
	if(0 > pid){
		perror("fork");
		return -1;
	}else if(0 == pid){
		close(fd[0]);
		close(fd[1]);
	}else{
#define MAX 100
		close(fd[0]);
		char buf[MAX];
		memset(buf, 0, sizeof(buf));
		fgets(buf, MAX, stdin);
		int len = strlen(buf);
		if(len != write(fd[1], buf, len)){
			printf("write fail.\n");
			return -1;
		}else
			printf("write done.\n");
	}
	return 0;
}
