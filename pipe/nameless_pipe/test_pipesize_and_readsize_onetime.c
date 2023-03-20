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
		close(fd[0]);
		int i = 0;
		while(1){
			char buf[] = "a";
			int len = strlen(buf);
			if(len != write(fd[1], buf, len)){
				printf("write fail.\n");
			}else{
				printf("NO:%d write str:%s :%d bytes\n", i++, buf, len);
			}
		}
		close(fd[1]);
		printf("son is over.\n");
	}else{
		//send
		printf("father is running.\n");
		close(fd[1]);
		char buf[MAX];
		int num;
		while(1){
			getchar();
			num = read(fd[0], buf, MAX - 1);
			if(0 > num){
				perror("read.\n");
			}else{
				buf[num] = 0;
				printf("%s", buf);
			}
		}
		close(fd[0]);
		printf("father is over.\n");
	}
	return 0;
}
