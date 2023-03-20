#include<stdio.h>
#include<signal.h>

void handler(int sig){
	printf("sig = %d\n", sig);
}

int main(){
	signal(SIGINT, handler);
	while(1){
		printf("Hello world!\n");
#if 1
		pause();
#else
		char ch;
		read(0, &ch, 1);
#endif
	}
	return 0;
}



