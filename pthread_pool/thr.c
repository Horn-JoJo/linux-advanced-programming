#include"thr.h"

//线程初始化
void thr_init(thr_t *obj, PFUN pfun, void *arg){
	obj->pfun = pfun;
	obj->arg = arg;
	obj->isAlive = 0;
	obj->isSusend = 1;
}

//统一线程函数来回调每一个线程对应绑定的工作函数
static void *routinue(void *arg){
	//传递工作线程结构体作为参数
	thr_t *this = (thr_t *)arg;
	printf("has already entered common thread logic: %p.\n", this);
	int oldstate;
	int oldtype;
	//设置线程取消状态和取消类型
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	
	//初始化工作线程的锁和条件变量
	pthread_mutex_init(&this->mutex, NULL);
	pthread_cond_init(&this->cond, NULL);
	//设置存活状态??
	this->isAlive = 1;

	while(1){
		pthread_mutex_lock(&this->mutex);
		if(this->isSusend){//如果当前线程挂起了，就等待
			pthread_cond_wait(&this->cond, &this->mutex);
		}
		pthread_mutex_unlock(&this->mutex);
		//否则就回调工作函数
		this->pfun(this->arg);//这里能不能修改成另一个工作函数，可以的。
	}
	return (void *)0;
}

int thr_start(thr_t *obj){
	if(obj->pfun && !obj->isAlive){
		return pthread_create(&obj->tid, NULL, routinue, (void *)obj);
	}
	return -1;
}


int thr_exit(thr_t *obj){
	if(obj->isAlive){
		pthread_cancel(obj->tid);//它杀
		pthread_mutex_destroy(&obj->mutex);//销毁互斥锁
		pthread_cond_destroy(&obj->cond);//销毁成员变量
		return 0;
	}
	return -1;
}

void thr_susend(thr_t *obj){
	pthread_mutex_lock(&obj->mutex);
	if(obj->isAlive && !obj->isSusend){
		obj->isSusend = 1;	
	}
	pthread_mutex_unlock(&obj->mutex);
}

void thr_resume(thr_t *obj){
	pthread_mutex_lock(&obj->mutex);
	if(obj->isAlive && obj->isSusend){
		obj->isSusend = 0;
	}
	pthread_mutex_unlock(&obj->mutex);
	pthread_cond_signal(&obj->cond);//发信号让cond_wait返回
}

int thr_isalive(thr_t *obj){
	return obj->isAlive;
}
