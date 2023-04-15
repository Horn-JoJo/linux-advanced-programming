#ifndef THR_H
#define THR_H
#include<pthread.h>

//定义了一个函数指针：指针类型为void* (void *)
typedef void *(*PFUN) (void *);

//工作线程结构体：将一个线程与一个工作函数进行关联
typedef struct __thr{
	PFUN pfun;//用于注册工作函数
	void *arg;//传递给工作函数的参数

	int isAlive;//判断线程是否创建
	int isSusend;//标志已经创建的线程的状态是运行态还是挂起态
	pthread_t tid;//线程号
	pthread_mutex_t mutex;//互斥锁
	pthread_cond_t cond;//条件变量
}thr_t;

//工作线程初始化：对传入的实例的每个成员进行初始化操作
void thr_init(thr_t *, PFUN pfun, void *);
//初始化工作线程
int thr_start(thr_t *);
//销毁工作线程
int thr_exit(thr_t *);
//工作线程挂起
void thr_susend(thr_t *);
//工作线程唤醒
void thr_resume(thr_t *);
//判断工作线程是否还存在
int thr_isalive(thr_t *);

#endif
