#include<stdio.h>

typedef struct data{
	int a;
	char *b;
	short c;
}*data_p;

void test(){
	printf("name: %s\n", __FUNCTION__);
}

int main(){
	void *p1;
	int *p2;
	char *p3;
	short *p4;
	data_p data;

	printf("p1 = %u\n", sizeof(p1));
	printf("p2 = %u\n", sizeof(p2));
	printf("p3 = %u\n", sizeof(p3));
	printf("p4 = %u\n", sizeof(p4));
	printf("data = %u\n", sizeof(data));
	

	void (*fun_p) ();
	fun_p = test;
	fun_p();
	test();

	int *a;
	a = (int *)1234;
	
	int b[10];//变量名a, 类型：int [10]
	int arr[2][2];//变量名，类型：int [2][2]
	int *c = b;
	c += 1;
	int *d = (int *)arr;
	int (*e)[2] = arr;

	return 0;
}
