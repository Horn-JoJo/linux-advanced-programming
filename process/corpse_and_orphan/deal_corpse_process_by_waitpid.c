#include<stdio.h>
#include<stdlib.h>

void son_process(int delay){
	printf("%s[%d]开始\n", __func__, getpid());
	while(delay--){
		sleep(1);
	}
	printf("%s[%d]结束\n", __func__, getpid());
	exit(0);
}

int main(){
	
	pid_t pid = fork();
	if(0 > pid){
		perror("fork");
		return -1;
	}else if(0 == pid){
		son_process(5);
	}else{
		pid = fork();
		if(0 > pid){
			perror("fork");
			return -1;
		}else if(0 == pid){
			son_process(10);
		}
		printf("%s[%d]开始\n", __func__, getpid());
		//waitpid(pid, NULL, 0);
		//waitpid(0, NULL, 0);
		waitpid(-1, NULL, 0);
		printf("%s[%d]结束\n", __func__, getpid());
	}
	return 0;
}
