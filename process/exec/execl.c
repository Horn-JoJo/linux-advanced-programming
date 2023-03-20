#include<stdio.h>
#include<unistd.h>


int main(){

	printf("func:%s:%d\n", __func__, __LINE__);	
	int second = 3;
	while(second){
		printf("距离占用进程空间还有%ds\n", second--);
		sleep(1);
	}

	//if(0 > execl("app", "./app", NULL)){
	if(0 > execl("APP/app", "hello", "work", NULL)){
		perror("execl");
		return -1;
	}

	printf("hello world!\n");
	return 0;
}
