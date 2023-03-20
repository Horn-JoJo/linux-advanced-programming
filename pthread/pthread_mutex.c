#include<stdio.h>
#include<pthread.h>

void *thread_1(void *arg){
	pthread_mutex_t *pmutex = arg;
	int i = 0;
	printf("pmutex:%p \n", pmutex);
	sleep(5);
	while(1){
		pthread_mutex_lock(pmutex);
		printf("%s : %d\n", __func__, i++);
		pthread_mutex_unlock(pmutex);
	}
}

void *thread_2(void *arg){
	pthread_mutex_t *pmutex = arg;
	int i = 0;
	printf("pmutex:%p \n", pmutex);
	sleep(5);
	while(1){
		pthread_mutex_lock(pmutex);
		printf("%s : %d\n", __func__, i++);
		pthread_mutex_unlock(pmutex);
	}
}

int main(){
	
	pthread_mutex_t mutex;
	int ret = pthread_mutex_init(&mutex, NULL);
	if(0 > ret){
		printf("pthread_mutex_init fail:%s\n", strerror(ret));
		return -1;
	}
	
	pthread_t tid[2];
	pthread_create(&tid[0], NULL, thread_1, &mutex);
	pthread_create(&tid[1], NULL, thread_2, &mutex);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);

	return 0;
}
