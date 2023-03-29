#include<stdio.h>
#include<errno.h>
#include<string.h>

int main(int argc, char **argv){
	char *filename = "1.txt";

	if(2 == argc){
		filename = argv[1];
	}

	FILE *fp = fopen(filename, "r");
	if(NULL == fp){
		printf("fopen %s fail: %s\n", filename, strerror(errno));
		return -1;
	}

#define BUFSZ 6
	char buf[BUFSZ];
	if(NULL == fgets(buf, BUFSZ, fp)){
		printf("read done.\n");
		goto ERR_STEP;
	}
	int len = strlen(buf);
	printf("fgets read %d bytes: %s\n", len, buf);

	while(1){
		len = fread(buf, sizeof(char), BUFSZ - 1, fp);
		if(!len){
			printf("fread read done.\n");
			break;
		}
		buf[len] = 0;
		printf("fread read %d bytes: %s\n", len, buf);
	}

ERR_STEP:
	fclose(fp);
	return 0;
}
