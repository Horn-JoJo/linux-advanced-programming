#include<stdio.h>
#include<pthread.h>

void *work(void *arg){
	int num = (int)arg;

	printf("%s:%d\n", __func__, num);
	sleep(1);
	return (void *)0;
}

unsigned long work1(unsigned long arg){
	
	char *str = (char *)arg;

	printf("%s:%s\n", __func__, str);
	sleep(3);
	return (unsigned long)0;
}

int main(){

	pthread_t tid[2];
	pthread_create(&tid[0], NULL, work, (void*)12345);
	pthread_join(tid[0], NULL);

	pthread_create(&tid[1], NULL, work1, "hello world");
	pthread_join(tid[1], NULL);

	printf("%s exit.\n", __func__);
	return 0;

}
