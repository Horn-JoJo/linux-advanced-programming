#include<stdio.h>
#include<string.h>
#include<unistd.h>

#define MAX 1024
int main(){
	int fd[2];
	
	if(0 > pipe(fd)){
		perror("pipe");
		return -1;
	}
	
	pid_t pid;
	pid = fork();
	if(0 > pid){
		perror("fork");
		return -1;
	}else if(0 == pid){
		//receive
		printf("son is running.\n");
		close(fd[1]);
		char buf[MAX];
		int num;
		num = read(fd[0], buf, MAX - 1);
		if(0 > num){
			perror("read.\n");
		}else{
			buf[num] = 0;
			printf("receive buf:%s %dbytes.\n", buf, num);
		}
		close(fd[0]);
		printf("son is over.\n");
	}else{
		//send
		printf("father is running.\n");
		sleep(1);
		close(fd[0]);
		char buf[] = "hello world";
		int len = strlen(buf);
		if(len != write(fd[1], buf, len)){
			printf("write fail.\n");
		}else{
			printf("write str:%s :%d bytes\n", buf, len);
		}
		close(fd[1]);
		printf("father is over.\n");
	}

	return 0;

}
