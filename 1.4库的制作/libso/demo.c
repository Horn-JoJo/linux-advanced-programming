#include<stdio.h>
#include<demo.h>

//static
static int demo(char *str){
	if(NULL != str){
		printf("shared object library:%s\n", str);
	}
	return -1;
}

static int  print(char *str){
	printf("%s :%d str = %s\n", __func__, __LINE__, str);
	return 0;
}

//声明定义初始化
struct sharedata data = {
	.value = 10,
	.prnmsg = demo,
	//.prnmsg = print,
};

/*
int i = 10;//声明定义初始化
int i;
i = 10;//赋值*/
