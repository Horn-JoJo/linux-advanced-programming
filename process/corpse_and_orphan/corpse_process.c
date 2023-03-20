#include<stdio.h>
#include<unistd.h>


int main(){
	int i = 0;
	
	pid_t pid = fork();
	if(-1 == pid){
		perror("fork");
		return -1;
	}else if(0 == pid){
		while(1){
			if(i > 3)
				break;
			printf("child---->其父进程:%d, 当前进程:%d, i = %d\n", getppid(), getpid(), i++);
			sleep(1);	
		}
		printf("我要变成僵尸了！！\n");
	}else{
		while(1){
			if(i > 10)
				break;
			printf("parent---->其父进程:%d, 当前进程:%d, i = %d\n", getppid(), getpid(), i++);
			sleep(1);
		}
	}

	return 0;
}
