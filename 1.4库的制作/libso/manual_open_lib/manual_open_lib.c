#include<stdio.h>
#include<dlfcn.h>
#include"../demo.h"

int main(int argc, char **argv){
	char *data = "hello lib world!";
	if(2 == argc){
		data = argv[1];
	}
	void *p = dlopen("/home/linux/2023/lib/libso/libdemo.so", RTLD_NOW);
	
	if(NULL == p){
		printf("dlopen fail.\n");
		return -1;
	}

	struct sharedata *pdata = dlsym(p, "data");
	printf("address:%p\n", pdata);
	if(NULL == pdata){
		perror("dlsym");
		goto NEXT_STEP;
	}
	//找到符号地址，回调
	pdata->prnmsg(data);
NEXT_STEP:
	dlclose(p);
	return 0;
}
