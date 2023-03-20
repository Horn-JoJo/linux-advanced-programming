#include<stdio.h>
#include<pthread.h>
#include<string.h>

typedef void * T;

T son_thread(void *arg){
	int oldstate;
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, &oldstate);
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
	int i = 0;
	while(1){
		printf("%s: %d\n", __func__, i++);
		sleep(1);
	}
#if 0
	return (T)999;
#endif
	pthread_exit(0);
}

int main(){
	pthread_t tid;
	
	int ret = pthread_create(&tid, NULL, son_thread, NULL);
	if(0 > ret){
		printf("pthread_create fail:%s\n.", strerror(-ret));
		goto ERR_STEP;
	}else{
		printf("pthread_create success!\n");
	}
	
	printf("%s:main run..\n", __func__);
	while(1){
		char ch = getchar();
		if('q' == ch || 'Q' ==  ch){
			pthread_cancel(tid);
			break;
		}
	}

	ret = pthread_join(tid, NULL);
	if(0 > ret){
		printf("pthread_join fail:%s\n", strerror(-ret));
		goto ERR_STEP;
	}
	
	printf("进程运行结束\n");
	
	return 0;
ERR_STEP:
	return -1;
}
