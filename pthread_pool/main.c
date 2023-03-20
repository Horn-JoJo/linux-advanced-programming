#include<stdio.h>
#include"thr.h"


void *work1(void *arg){
	int number = (int)arg;

	printf("%s:is printf number:%d\n", __func__, number);
	sleep(1);
	return (void *)0;
}

char *work2(void *arg){
	char *str = (char *)arg;
	printf("%s is printf a str:%s\n", __func__, str);
	sleep(1);
	return str;
}

int main(){

	thr_t thread[2];
	
	thr_init(&thread[0], work1, (void *)12345);
	thr_init(&thread[1], work2, "hello world");

	thr_start(&thread[0]);
	thr_start(&thread[1]);

	while(1){
		char ch = getchar();
		getchar();
		if('c' == ch || 'C' == ch){
			thr_exit(&thread[0]);
			thr_exit(&thread[1]);
			break;
		}else if('r' == ch){
			thr_resume(&thread[0]);
		}else if('R' == ch){
			thr_resume(&thread[1]);
		}else if('s' == ch){
			thr_susend(&thread[0]);
		}else if('S' == ch){
			thr_susend(&thread[1]);
		}
	}

	printf("----------main over------------------\n");

	return 0;
}
