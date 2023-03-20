#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
#include <string.h>
#include"pipename.h"

int main(){

	if(0 > mkfifo(PIPENAME, 0666)){
		if(EEXIST != errno){
			perror("mkfifo");
			return -1;
		}
	}

	int rfd = open(PIPENAME, O_RDONLY /*| O_NONBLOCK*/);
	if(0 > rfd){
		perror("open");
		goto ERR_STEP;
	}

#define MAX 1024
	char buf[MAX];
	int size = read(rfd, buf, MAX - 1);
	if(0 > size){
		printf("read");
		goto ERR_STEP1;
	}
	buf[size] = 0;
	printf("recv %d bytes:%s\n", size, buf);

ERR_STEP1:
	close(rfd);
ERR_STEP:
	remove(PIPENAME);
	return 0;
}
