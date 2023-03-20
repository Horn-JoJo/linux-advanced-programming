#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>

int daemon_init(){
	pid_t pid = fork();
	if(0 > pid){
		perror("fork");
		goto ERR_STEP;
	}else if(0 < pid){
		exit(0);
	}else{
		printf("fork and make father die success!\n");
	}

	if (0 > setsid()){
		perror("setsid");
		goto ERR_STEP;
	}else{
		printf("set a new session success!\n");
	}

	if(0 > chdir("/home/linux/2023/")){
		perror("chdir");
		goto ERR_STEP;
	}else{
		printf("set a new workpath success!\n");
	}

	if(0 > umask(0022)){
		perror("umask");
		goto ERR_STEP;
	}
	printf("set a new mask success!\n");

	int maxfd = getdtablesize();
	for(int i = 0; i < maxfd; i++){
		printf("正在关闭文件描述符:%d\n", i);
		close(i);
	}
	//这里不能打印信息
	printf("has closed all fds\n");

	printf("deamon init success!\n");

	return 0;
ERR_STEP:
	return -1;
}



int main(int argc, char **argv){
	if (-1 == daemon_init()){
		return -1;
	}

	//因为已经关闭了输入输出文件描符所有不会输出到屏幕
	printf("守护进程工作逻辑！！！\n");
	char *filename = "1.txt";
	if(2 == argc){
		filename = argv[1];
	}

	FILE *fp = fopen(filename, "a+");
	if(NULL == fp){
		perror("fopen");
		return -1;
	}

#define MAX 36
	char buf[MAX];
	int i = 1;
	while(1){
		snprintf(buf, MAX, "happy %d s\n", i++);	
		int len = strlen(buf);
		if(len != fwrite(buf, sizeof(char), len, fp)){
			break;
		}
		sleep(1);
		fflush(fp);
	}

	fclose(fp);
	return 0;
}
