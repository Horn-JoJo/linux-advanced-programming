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
			if(i > 10)
				break;
			printf("child---->父进程:%d, 当前进程:%d, i = %d\n", getppid(), getpid(), i++);
			sleep(1);	
		}
	}else{
		while(1){
			if(i > 10)
				break;
			printf("parent---->父进程:%d, 当前进程:%d, i = %d\n", getppid(), getpid(), i++);
			sleep(1);
		}
	}

	return 0;
}
