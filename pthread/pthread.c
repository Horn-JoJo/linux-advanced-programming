#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define err_log(log)\
	do{\
		printf(log);\
		return -1;\
	}while(0)

struct POS{
	int x;
	int y;
};

typedef struct POS POS;

void *son_thread(void *arg)
{
	int i = 0;
	while (1)
	{
		printf("fun[%s] is working %ds.\n", __func__, ++i);
		if (i >= 3) break;
		sleep(1);
	}
	static POS inf = {
		.x = 220,
		.y = 110
	};
#if 0//线程函数返回值
	//1.返回整型数据
	return (void *)123;
	//2.返回字符串的首地址
	//return (void *)arg;
	
	//4.返回结构体的地址
	//return (void *)&inf;
#else
	//pthread_exit((void *)"我是你爸爸");
	
	//3.返回整数数组的首地址
	//static int a[4] = {110, 2220, 478, 890};
	//pthread_exit((void *)a);
	
	//4.返回结构体的地址
	pthread_exit((void *)&inf);
#endif
}


int main()
{
	pthread_t pid;
	if (0 > pthread_create(&pid, NULL, son_thread, "hello world")) err_log("pthread_create failed.\n");
	

	//任意指针类型都行！！！因为有4字节空间，可以直接存储数据，也可以存储数据的地址！！！！通常写成void *
	void *retval;
	//printf("POS* = %dbytes, void * = %dbytes\n", sizeof(POS *), sizeof(char *));
	pthread_join(pid, &retval);
	//1.当线程函数返回的是整数
	//printf("son_thread return val = %d\n", (int)retval);	
	
	//2.当线程函数返回的是字符串
	//printf("son_thread return val = %s\n", (char *)retval);	

	//3.当线程函数返回的是整型数组的首地址
	//printf("son_thread return val = %d\n", ((int *)retval)[0]);
	//printf("son_thread return val = %d\n", ((int *)retval)[1]);
	//printf("son_thread return val = %d\n", ((int *)retval)[2]);
	//printf("son_thread return val = %d\n", ((int *)retval)[3]);
	
	//4.当线程函数返回结构体的地址
	printf("son_thread return val (%d, %d)\n", ((POS*)retval)->x, ((POS*)retval)->y);
	
	//验证主线程和子线程默认是绑定的状态，因此join时会等子线程运行完！！！然后主线程才会退出！！！
	printf("fun[%s] is exiting.\n", __func__);
	return 0;
}
