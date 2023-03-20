#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

typedef void *(*PFUN) (void *);

typedef struct{
	PFUN pfun;
	void *arg;
}thr_t;

pthread_rwlock_t rwlock;

void print(char *str){
	printf("======%s====start========\n", str);
	sleep(5);
	printf("======%s====end==========\n", str);
}

void *readfun1(void *arg){
	char *pstr = (char *)arg;
	pthread_rwlock_rdlock(&rwlock);
	print(pstr);
	pthread_rwlock_unlock(&rwlock);
}

void *readfun2(void *arg){
	char *pstr = (char *)arg;
	pthread_rwlock_rdlock(&rwlock);
	print(pstr);
	pthread_rwlock_unlock(&rwlock);
}

void *writefun1(void *arg){
	char *pstr = (char *)arg;
	pthread_rwlock_wrlock(&rwlock);
	print(pstr);
	pthread_rwlock_unlock(&rwlock);
}

void *writefun2(void *arg){
	char *pstr = (char *)arg;
	pthread_rwlock_wrlock(&rwlock);
	print(pstr);
	pthread_rwlock_unlock(&rwlock);
}

thr_t thr_pool[] = {
	{readfun1, "1readthread"},
	{readfun2, "2readthread"},
	{writefun1, "1writethread"},
	{writefun2, "2wrirethread"},
};

#define ARRYZISE(a) ((sizeof(a)) / (sizeof(a[0])))

int main(){
	
	pthread_rwlock_init(&rwlock, NULL);

	pthread_t tid[ARRYZISE(thr_pool)];
	for(int i = 0; i < ARRYZISE(tid); i++){
		if(i == 0 || i == 1)
			continue;
		pthread_create(&tid[i], NULL, thr_pool[i].pfun, thr_pool[i].arg);
	}
	
	//pthread_join(tid[0], NULL);
	//pthread_join(tid[1], NULL);
	pthread_join(tid[2], NULL);
	pthread_join(tid[3], NULL);

	pthread_rwlock_destroy(&rwlock);

	return 0;
}
