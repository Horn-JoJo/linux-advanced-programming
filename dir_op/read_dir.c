#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>

int main(int argc, char **argv){
	char *dirname = "/home";

	if(2 == argc){
		dirname = argv[1];
	}

	DIR *dirp = opendir(dirname);
	if(NULL == dirp){
		perror("opendir");
		return -1;
	}

	while(1){
		struct dirent *contexp = readdir(dirp);
		if(NULL == contexp){
			printf("\nread %s done.\n", dirname);
			break;
		}
		switch(contexp->d_type){
		case DT_DIR:
			printf("dirname-[%s] is 目录文件\n", contexp->d_name);
			break;
		case DT_BLK:
			printf("dirname-[%s] is 块设备文件\n", contexp->d_name);
			break;
		case DT_CHR:
			printf("dirname-[%s] is 字符设备文件\n", contexp->d_name);
			break;
		case DT_FIFO:
			printf("dirname-[%s] is 管道设备文件\n", contexp->d_name);
			break;
		case DT_LNK:
			printf("dirname-[%s] is 符号链接文件\n", contexp->d_name);
			break;
		case DT_REG:
			printf("dirname-[%s] is 普通文件\n", contexp->d_name);
			break;
		case DT_SOCK:
			printf("dirname-[%s] is 套接字文件\n", contexp->d_name);
			break;
		default:
			printf("dirname-[%s] is 其他文件\n", contexp->d_name);
			break;
		
		};
		//printf("name : %s\n", contexp->d_name);
	}

	return 0;
}
