#include<stdio.h>
#include<pthread.h>
#include<unistd.h>


int isRun = 0;
pthread_cond_t cond;
pthread_mutex_t mutex;

void *sleeper(void *arg){
	printf("thread[%s] is running:default suspend status\n", __func__);
	int i = 1;
	while(1){
		pthread_mutex_lock(&mutex);
		if(!isRun){
			pthread_cond_wait(&cond, &mutex);
			i = 1;
		}
		pthread_mutex_unlock(&mutex);
		printf("simulating thread is running! %ds \n", i++);
		sleep(1);
	}
}



int main(){
	
	pthread_t tid;
	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex, NULL);
	pthread_create(&tid, NULL, sleeper, NULL);

	while(1){
		printf("start/stop thread:\n");
		char ch = getchar();
		getchar();//recycle garbage characters
		if('r' == ch){
			pthread_mutex_lock(&mutex);
			if(!isRun){
				isRun = 1;
				pthread_cond_signal(&cond);
			}
			pthread_mutex_unlock(&mutex);
		}else if('s' == ch){
			pthread_mutex_lock(&mutex);
			if(isRun){
				isRun = 0;		
			}
			pthread_mutex_unlock(&mutex);
		}else if('q' == ch){
			pthread_cancel(tid);
			break;
		}
	}

	pthread_join(tid, NULL);

	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);

	return 0;
}
