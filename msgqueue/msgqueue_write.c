#include<stdio.h>
#include<string.h>
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
	return 0;
}




int main() {

	int msqid = open_msgqueue();
	if (0 > msqid) {
		return -1;
	}

#define MAX 1024
	char buf[MAX];
	typedef struct {
		long mtype;
		char mtext[MAX];
	}pack_t;

	pack_t pack;
	while(1) {
		printf("Please input msg:\n");
		fgets(pack.mtext, MAX, stdin);
		int len = strlen(pack.mtext);
		pack.mtext[len - 1] = 0;
		pack.mtype = rand() % 10;
		
		int size = msgsnd(msqid, &pack, MAX, 0);
		if (0 > size) {
			perror("msgsnd");
			return -1;
		}
		printf("<msgqueue_snd>:\npack_type[%ld];\npack_text:%s;\npack_capacity[%dB]\n", pack.mtype, pack.mtext, MAX);
		puts("====================================================================================================");
	}
	
	return 0;
}
