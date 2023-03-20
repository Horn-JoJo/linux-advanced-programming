#include<stdio.h>
#include<signal.h>
#include<time.h>
#include<unistd.h>
#include<sys/types.h>

void handler(int sig) {
	printf("%s :%d\n", __func__, sig);
	time_t t  = time(NULL);
	struct tm *ptm = localtime(&t);
	printf("cur_time:%d/%d/%d %02d:%02d:%02d\n", ptm->tm_year + 1900, ptm->tm_mon + 1,
			ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
#if 1
	alarm(3);
#else
	sleep(3);
	raise(sig);
#endif
}


int main(){
	signal(SIGALRM, handler);
	alarm(3);
	while(1){
		printf("-------------1---------\n");
		pause();
		printf("-------------2--------\n");
	}
	printf("-------------end--------\n");
	return 0;
}
