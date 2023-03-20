#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<sys/ipc.h>
#include<errno.h>
#include<sys/shm.h>

int open_shm(size_t size) {
	
	//acquire key value
	key_t key = ftok(".", 'a');
	if (0 > key) {
		perror("ftok");
		return -1;
	}

	//acquire id
	int shmid = shmget(key, size, 0666);
	if (0 > shmid) {
		perror("shmget");
		return -1;
	}

	printf("open shm successfully.\n");
	return shmid;
}

int del_shm(int shmid) {
	struct shmid_ds t;
	if (0 > shmctl(shmid, IPC_STAT, &t)) {
		perror("shmctl");
		return -1;
	}

	if (0 == t.shm_nattch) {
		if (0 > shmctl(shmid, IPC_RMID, NULL)) {
			perror("shmctl");
			return -1;
		}else {
			printf("delete shared memory successfully\n");
		}
	}
	return 0;
}

int main() {

	int shmid = open_shm(1024);
	if(0 > shmid) {
		printf("open shm fail.\n");
		return -1;
	}

	//map physical address into logic address
	char *p_shm = shmat(shmid, NULL, 0);
	
#define MAX 1024
	char buf[MAX];
	printf("Please input:\n");
	fgets(buf, MAX - 1, stdin);
	int len = strlen(buf);
	buf[len - 1] = 0;
	strncpy(p_shm, buf, len);
	//unmap
	shmdt(p_shm);
	del_shm(shmid);
	return 0;
}
