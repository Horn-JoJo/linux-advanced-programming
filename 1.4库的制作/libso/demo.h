#ifndef DEMO_H
#define DEMO_H

//定义一个函数指针类型
typedef int (*fun_t)(char *str);

/*
typedef int T;
int i;
int arr[10];//数组类型是int[10]，数组成员类型是int
*/

struct sharedata{
#if 0
	int (*prnmsg) (char *str);
#else
	fun_t prnmsg;
#endif
	int value;
};
extern struct sharedata data;//声明一个全局的外部变量，不是定义，因为头文件只能作声明
static int demo(char *str);//没有函数体-函数声明
static int print(char *);
#endif
