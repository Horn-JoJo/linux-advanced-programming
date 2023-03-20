#include<stdio.h>
#include<string.h>
#include<errno.h>
int main(int argc, char **argv){
	char *filename = "hello world";
	if(argc == 2){
		filename = argv[1];
	}

	FILE *fp = fopen(filename, "w");
	if(NULL == fp){
		printf("fopen %s fail:%s\n", filename, strerror(errno));
		return -1;
	}

	printf("filename:%s\n", filename);
	return 0;

}
