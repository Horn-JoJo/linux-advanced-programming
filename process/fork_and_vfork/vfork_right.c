#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>


int main(){
	int i = 0;
	pid_t pid = vfork();
	if(-1 == pid){
		perror("vfork");
	}else if(0 == pid){
		while(1){
			if(i > 10)
				break;
			printf("ppid :%u, cur_pid:%u, i = %d\n", getppid(), getpid(), ++i);
			sleep(1);
		}
	}else{
		while(1){
			if(i > 20)
				break;
			printf("ppid :%u, cur_pid:%u, i = %d\n", getppid(), getpid(), ++i);
			sleep(1);
		}
	}
	exit(0);
	//return 0;
}
