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
	int arr[2][10];//变量名，类型：int [2][10] 默认是arr的一个执向10个int长度的常指针
	int *c = b;
	c += 1;
	//int *d = arr;//会警告，类型其实是不匹配的！！！这很危险！！！
	int *d = (int *)arr;//把arr转化为指向一个int长度的地址 方便一个一个数据的访问
	//int (*e)[2] = arr; //警告，这其实是很危险的，因为默认arr为一个执向10个int长度的常指针 
	int (*e)[10] = arr; //一个指针的跨度为10个int, 也就是每次访问都是跨度为2个int后的元素 

	int arr1[3][9][7];
	int (*f)[9][7] = arr1; 

	return 0;
}
