#include<stdio.h>
#include<stdlib.h>



int main(){
	if(0 > system("./app1 hello world")){
		perror("system");
	}else{
		printf("system.c process continue to run.\n");
	}
	return 0;
}
