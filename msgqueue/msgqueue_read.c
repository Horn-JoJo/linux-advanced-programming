#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<errno.h>
#include<sys/msg.h>

int open_msgqueue() {
	key_t key = ftok(".", 'a');
	if (0 > key) {
		perror("ftok");
		return -1;
	}
	
	int msqid = msgget(key, IPC_CREAT | IPC_EXCL | 0666 );
	if (0 > msqid) {
		if (EEXIST == errno) {
			msqid = msgget(key, 0666);
			if (0 <= msqid) {
				printf("open msgqueue successfully.\n");
				return msqid;
			}
			printf("open msgqueue failed.\n");
			return -1;
		}
		printf("create msgqueue failed.\n");
		return -1;
	}
	printf("create msgqueue successfully.\n");
	return msqid;
}

int del_msgqueue(int msqid) {
	if (0 > msgctl(msqid, IPC_RMID, NULL)) {
		perror("msgctl-delete");
		return -1;
	}
	printf("del_msgqueue successfully.\n");
	return 0;
}


int id = -1;
void handler(int sig) {
	del_msgqueue(id);
	exit(0);
}

int main() {

	id = open_msgqueue();
	if (0 > id) {
		return -1;
	}

	signal(SIGINT, handler);

#define MAX 1024
#define RCVALL 0
#define RCV3 3
#define RCVN5 -5
	char buf[MAX];
	typedef struct {
		long mtype;
		char mtext[MAX];
	}pack_t;

	pack_t pack;
	while(1) {
		printf("waiting for msg...\n");
		
		int size = msgrcv(id, &pack, MAX, RCVN5, 0);
		if (0 > size) {
			perror("msgsnd");
			return -1;
		}
		printf("<msgqueue_rcv>:\npack_type[%ld];\npack_size:%dB;\npack_text:%s;\npack_capacity:%dB\n", pack.mtype, size, pack.mtext, MAX);
		puts("==========================================================================================================================");
	}
	return 0;
}
