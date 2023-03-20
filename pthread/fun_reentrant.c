#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

typedef void * T;

void loop(const char *pthread_name, pthread_t tid){
	int i = 0;
	while(1){
		printf("[%s]:[%lu] %d s\n", pthread_name, tid, i++);
		sleep(1);
	}
}

T son_thread(T arg){
	loop(__func__, (pthread_t)arg);
	return (T)0;
}

int main(){

	pthread_t tid;
	int ret = pthread_create(&tid, NULL, son_thread, (void *)tid);
	if(0 > ret){
		printf("pthread_create fail\n");
		return -1;
	}
	pthread_t main_tid = pthread_self();
	loop(__func__, main_tid);

	return 0;
}
