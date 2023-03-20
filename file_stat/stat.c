#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<time.h>


int main(int argc, char **argv){
	char *filename = "stat.c";

	if(2 == argc){
		filename = argv[1];
	}

	struct stat info;

	if(-1 == stat(filename, &info)){
		perror("stat");
		return -1;
	}

	if(S_ISREG(info.st_mode)){
		printf("普通文件\n");
	}else if(S_ISDIR(info.st_mode)){
		printf("目录文件\n");	
	}else{
		printf("其他文件\n");
	}

	printf("文件大小：%lu bytes\n", info.st_size); 
	printf("最后访问时间：%s\n", ctime(&info.st_atime));
	return 0;
}
