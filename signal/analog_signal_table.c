#include<stdio.h>
#include<unistd.h>

#define SIG_IGN NULL
#define SIG_DFL defproc
#define SIGMAX 12
typedef void (*CALLBACK) (int);

CALLBACK SigArray[SIGMAX];

void defproc(int sig) {
	printf("%s:sig = %d\n", __func__, sig);

	//kill | suspend process
}

void handler(int sig) {
	printf("%s:sig = %d\n", __func__, sig);
}

int signal (int sig, CALLBACK pfun) {
	if (sig > 0 && sig <= SIGMAX) {
		if (SIG_DFL != pfun) {
			SigArray[sig - 1] = pfun;
		}
		return 0;
	}
	return -1;
}

int kill (int sig) {
	if (sig > 0 && sig <= SIGMAX) {
		if (SIG_IGN != SigArray[sig - 1]) {
			SigArray[sig - 1](sig);
		}else 
			return -1;
	}
	return 0;
}

int main() {
	for (int i = 0; i < SIGMAX; i++) {
		SigArray[i] = SIG_DFL;
	}	
		
	signal(2, handler);
	sleep(1);
	kill(2);
	sleep(1);
	kill(12);

	return 0;
}
