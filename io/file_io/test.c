#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/fcntl.h>
#include<errno.h>


void write_to_file(char *filename){
	int fd = open(filename,O_RDWR | O_CREAT | O_EXCL, 0666);
	if(-1 == fd){
		if(EEXIST == errno){
			fd = open(filename, O_RDWR | O_APPEND);//O_TRUNC
			if(-1 == fd){
				perror("open");
				return;
			}
		}else{
			printf("creat file %s fail:%s\n", filename, strerror(errno));
			return;
		}
	}
	printf("open file %s success!\n", filename);
	printf("Please input:\n");

#define MAX 1024
	char buf[MAX + 1];
	int len = read(0, buf, MAX);
	if(-1 == len){
		perror("read");
		goto ERR_STEP;
	}
	buf[len] = 0;
	
	if(len != write(fd, buf, len)){
		printf("write fail.\n");
	}else{
		printf("write done.\n");
	}

ERR_STEP:
	close(fd);
}

int main(int argc, char **argv){
	char *filename = "default.txt";
	if(2 == argc){
		filename = argv[1];
	}
	write_to_file(filename);
}
