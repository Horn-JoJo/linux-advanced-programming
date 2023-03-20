#include<stdio.h>
#include<sys/types.h>
#include<wait.h>
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
		printf("我快要变成僵尸了！！，赶紧通知父进程作回收清理事务安排\n");
	}else{
		int status;
		wait(&status);
		printf("parent---->已经收到:返回状态:%d， 已经清理子进程资源\n", WEXITSTATUS(status));
		while(1){
			if(i > 10)
				break;
			printf("parent---->其父进程:%d, 当前进程:%d, i = %d\n", getppid(), getpid(), i++);
			sleep(1);
		}
	}
	return 123;
}
