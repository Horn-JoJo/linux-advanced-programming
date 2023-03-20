#include<stdio.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>

int main(){
	int fd;
	while(1){
		fd = open("number_of_fd.c", O_RDWR);
		//fd = open("number_of_fd.c", "r");
		if(0 > fd){
			perror("open");
			break;
		}
		printf("fd= %d\n", fd);
	}
	close(fd);
	return 0;
}
