#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<dirent.h>

int rddir(const char *dirname){

	DIR *dirp = opendir(dirname);
	if(NULL == dirp){
		perror("opendir");
		return -1;
	}

	while(1){
		struct dirent *contexp = readdir(dirp);
		if(NULL == contexp){
			printf("read %s done.\n", dirname);
			puts("**************************");
			break;
		}
		switch(contexp->d_type){
		case DT_DIR:
			if(strcmp(".", contexp->d_name) && strcmp("..", contexp->d_name))
			{
				printf("[%s]:目录文件\n", contexp->d_name);
				char path[1024];
				snprintf(path, 1024, "%s/%s", dirname, contexp->d_name);
				rddir(path);
			}
			//printf("[%s]:目录文件\n", contexp->d_name);
			break;

		case DT_BLK:
			printf("[%s]:块文件设备\n", contexp->d_name);
			break;

		case DT_CHR:
			printf("[%s]:字符设备文件\n", contexp->d_name);
			break;

		case DT_LNK:
			printf("[%s]:符号链接文件\n", contexp->d_name);
			break;

		case DT_SOCK:
			printf("[%s]:套接字文件\n", contexp->d_name);
			break;

		case DT_FIFO:
			printf("[%s]:管道文件\n", contexp->d_name);
			break;

		case DT_REG:
			printf("[%s]:普通文件\n", contexp->d_name);
			break;

		default:
			printf("[%s]:其他文件\n", contexp->d_name);
			break;

		};
	}
	closedir(dirp);
	return 0;
}



int main(int argc, char **argv){
	char *dirname = "/home";

	if(2 == argc){
		dirname = argv[1];
	}

	rddir(dirname);
	return 0;
}
