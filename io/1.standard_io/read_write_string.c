#include<stdio.h>
#include<errno.h>
#include<string.h>

int main(int argc, char **argv){
	char *filename = "1.txt";
	
	FILE *fp = fopen(filename, "r+");
	if(NULL == fp){
		printf("fopen %s fail: %s\n", filename, strerror(errno));
		goto ERR_STEP;
	}

	printf("Please input something:");

#define BUFSIZE 512
	char buf[BUFSIZE];
	if(NULL == fgets(buf, BUFSIZE, stdin)){
		printf("read done.\n");
		goto ERR_STEP;
	}

	int len = strlen(buf);
	buf[--len] = 0;

	if(len != fwrite(buf, sizeof(char), len, fp)){
		printf("write fail.\n");
		goto ERR_STEP;
	}
	
	if(-1 == fseek(fp, 0, SEEK_SET)){
		perror("fseek fail");
		goto ERR_STEP;
	}

#define RDMAX 16
	char rdbuf[RDMAX];
	while(1){
		len = fread(buf, sizeof(char), RDMAX - 1, fp);
		if(!len){
			printf("read done.\n");
			break;
		}
		buf[len] = 0;
		printf("fread %d bytes :%s\n", len, buf);
	}

ERR_STEP:
	fclose(fp);
	return 0;
}
