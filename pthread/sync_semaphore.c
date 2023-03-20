#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>

typedef void * T;

sem_t a, b;

T producer(T arg){
	printf("%s is running\n", __func__);
	while(1){
		sem_wait(&b);
		printf("producer---------------------------\n");
		sleep(3);	
		sem_post(&a);
	}
}


T consumer(T arg){
	printf("%s is running\n", __func__);
	while(1){
		sem_wait(&a);
		printf("consumer---------------------------\n");
		sem_post(&b);
	}
}

int main(){
	
	sem_init(&a, 0, 0);
	sem_init(&b, 0, 1);
	pthread_t tid[2];

	pthread_create(&tid[0], NULL, consumer, NULL);
	sleep(5);
	pthread_create(&tid[1], NULL, producer, NULL);

	pthread_join(tid[0], NULL);
	pthread_join(tid[1], NULL);
	
	sem_destroy(&a);
	sem_destroy(&b);

	return 0;
}
