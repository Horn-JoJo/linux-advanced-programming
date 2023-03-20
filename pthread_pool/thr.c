#include"thr.h"

void thr_init(thr_t *obj, PFUN pfun, void *arg){
	obj->pfun = pfun;
	obj->arg = arg;
	obj->isAlive = 0;
	obj->isSusend = 1;
}


static void *routinue(void *arg){
	thr_t *this = (thr_t *)arg;
	printf("has already entered common thread logic: %p.\n", this);
	int oldstate;
	int oldtype;
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

	pthread_mutex_init(&this->mutex, NULL);
	pthread_cond_init(&this->cond, NULL);
	this->isAlive = 1;

	while(1){
		pthread_mutex_lock(&this->mutex);
		if(this->isSusend){
			pthread_cond_wait(&this->cond, &this->mutex);
		}
		pthread_mutex_unlock(&this->mutex);
		this->pfun(this->arg);
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
		pthread_cancel(obj->tid);
		pthread_mutex_destroy(&obj->mutex);
		pthread_cond_destroy(&obj->cond);
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
	pthread_cond_signal(&obj->cond);
}

int thr_isalive(thr_t *obj){
	return obj->isAlive;
}
