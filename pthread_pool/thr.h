#ifndef THR_H
#define THR_H
#include<pthread.h>

typedef void *(*PFUN) (void *);

typedef struct __thr{
	PFUN pfun;
	void *arg;

	int isAlive;
	int isSusend;
	pthread_t tid;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}thr_t;

void thr_init(thr_t *, PFUN pfun, void *);
int thr_start(thr_t *);
int thr_exit(thr_t *);
void thr_susend(thr_t *);
void thr_resume(thr_t *);
int thr_isalive(thr_t *);

#endif
