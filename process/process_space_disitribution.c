#include<stdio.h>
#include<stdlib.h>

int global_var;//编译器自动优化赋值为0
static int static_global_val;

char *pstr = "hello world";

void test(){

	int local_var;
	static int static_local_var;
	int *p = malloc(sizeof(int));

	printf("常量:%p\n", pstr);
	printf("静态全局变量:%p\n", &static_global_val);
	printf("静态局部变量:%p\n", &static_local_var);
	printf("全局变量:%p\n", &global_var);
	printf("堆区:%p\n", p);
	printf("局部变量(栈区):%p\n", &local_var);
}

int main(){

	printf("代码区:%p\n", test);
	test();

	return 0;
}
