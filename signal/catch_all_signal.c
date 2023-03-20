#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<errno.h>


void handler(int sig) {
	printf("%s: sig: %d\n", __func__, sig);
}

int main() {
	
	int i;
	for (i = 1; i <= 64; i++) {
		if (SIG_ERR == signal(i, handler)){
			printf("sig: %d:%s\n", i, strerror(errno));
		}
	}
	
#define MAX 36
	char buf[MAX];
	while(1) {
		printf("Please input signum:");
		fgets(buf, MAX, stdin);
		int len = strlen(buf);
		buf[len - 1] = 0;

		int signum = atoi(buf);
		if(0 > raise(signum)) {
			perror("raise");
		}
	}
	return 0;
}
