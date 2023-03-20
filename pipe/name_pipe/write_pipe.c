#include<stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include"pipename.h"

int main(){
	
	int wfd = open(PIPENAME, O_WRONLY);
	if(0 > wfd){
		perror("open");
		return -1;
	}
	
	printf("please input:\n");
#define MAX 1024
	char buf[MAX];
	fgets(buf, MAX, stdin);

	int len = strlen(buf);
	if(len == write(wfd, buf, len)){
		printf("send %d bytes:%s\n", len, buf);
	}else{
		perror("write");	
	}

	sleep(3);
	printf("-------------over------------------\n");
	

	close(wfd);
	return 0;
}
