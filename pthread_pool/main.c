#include<stdio.h>
#include"thr.h"

//工作函数1：//打一个数字
void *work1(void *arg){
	int number = (int)arg;

	printf("%s:is printf number:%d\n", __func__, number);
	sleep(1);
	return (void *)0;
}

//工作函数2：打印字符串
char *work2(void *arg){
	char *str = (char *)arg;
	printf("%s is printf a str:%s\n", __func__, str);
	sleep(1);
	return str;
}

int main(){

	thr_t thread[2];//定义两个工作线程变量
	
	//工作线程初始化：对工作线程结构体成员赋值
	thr_init(&thread[0], work1, (void *)12345);
	thr_init(&thread[1], work2, "hello world");

	//创建工作线程：会回调真正的线程函数，然后真正的线程函数会取回调工作线程里的工作函数。
	//当然初始的时候默认处于挂起状态
	thr_start(&thread[0]);
	thr_start(&thread[1]);

	while(1){
		char ch = getchar();
		getchar();
		if('c' == ch || 'C' == ch){
			thr_exit(&thread[0]);
			thr_exit(&thread[1]);
			break;
		}else if('r' == ch){
			thr_resume(&thread[0]);
		}else if('R' == ch){
			thr_resume(&thread[1]);
		}else if('s' == ch){
			thr_susend(&thread[0]);
		}else if('S' == ch){
			thr_susend(&thread[1]);
		}
	}

	printf("----------main over------------------\n");

	return 0;
}
