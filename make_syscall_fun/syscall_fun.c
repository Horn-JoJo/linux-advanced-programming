#define _GNU_SOURCE         /* See feature_test_macros(7) */
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>

int myopen(const char *pathname, int flags){
	return syscall(SYS_open, pathname, flags);
}

int myread(int fd, void *buf, size_t count){
	return syscall(SYS_read, fd, buf, count);
}

int mywrite(int fd, void *buf, size_t count){
	return syscall(SYS_write, fd, buf, count);
}

int myclose(int fd){
	return syscall(SYS_close, fd);
}


int main(int argc, char **argv){
	char *filename = "syscall_fun.c";
	
	if(2 == argc){
		filename = argv[1];
	}
	int fd = myopen(filename, O_RDONLY);
	if(fd < 0){
		perror("myopen");
	}

#define MAX 5
	char buf[MAX + 1] = {0};

	while(1){
		int len;
		if(len = myread(fd, buf, MAX)){
			buf[len] = 0;
			printf("%s", buf);
		}else{
			printf("\nread %s done.\n", filename);
			break;
		}
	}

	myclose(fd);
	return 0;
}
