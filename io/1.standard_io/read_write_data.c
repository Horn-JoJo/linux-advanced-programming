#include<stdio.h>
#include<errno.h>
#include<string.h>

int main(int argc, char **argv){
	char *filename = "set.dat";

	FILE *fp = fopen(filename, "a+");
	if(NULL == fp){
		perror("fopen");
		goto ERR_STEP;
	}

	if(-1 == fseek(fp, 0, SEEK_SET)){
		perror("fseek");
		goto ERR_STEP;
	}
	
	int val = 0x12345678;
	double d[1] = {0.123456};
	char str[] = "hello";
	char str2[] = " world";

	if(1 != fwrite(&val, sizeof(int), 1, fp)){
		printf("write int to file fail.\n");
		goto ERR_STEP;
	}
	if(1 != fwrite(d, sizeof(double), 1, fp)){
		printf("write double to file fail.\n");
		goto ERR_STEP;
	}

	int len = strlen(str);
	len++;
	if(len != fwrite(str, sizeof(char), len, fp)){
		printf("write str to file fail.\n");
		goto ERR_STEP;
	}
	len = strlen(str2);
	len++;
	if(len != fwrite(str2, sizeof(char), len, fp)){
		printf("write str2 to file fail.\n");
		goto ERR_STEP;
	}

	if(0 > fseek(fp, 0, SEEK_SET)){
		perror("fseek");
		goto ERR_STEP;
	}

	int rdint;
	double rdd;
#define BUSZ 512
	char rdbuf[BUSZ];

	if(1 != fread(&rdint, sizeof(int), 1, fp)){
		printf("fread rdint fail.\n");
		goto ERR_STEP;
	}
	printf("rdint :0x%x\n", rdint);

	if(1 != fread(&rdd, sizeof(double), 1, fp)){
		printf("fread rdd fail.\n");
		goto ERR_STEP;
	}
	printf("rdd :%g\n", rdd);
	
	len = fread(rdbuf, sizeof(char), BUSZ, fp);
	printf("rdbuf %d bytes.\n", len);

	printf("str :%s\n", rdbuf);

	len = strlen(rdbuf);
	len++;
	char *p = rdbuf;
	p += len;
	
	printf("str2 :%s\n", p);

ERR_STEP:
	fclose(fp);
	return 0;

}
