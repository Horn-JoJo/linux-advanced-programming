#include<stdio.h>
#include<signal.h>
#include<sys/types.h>
#include<errno.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/shm.h>


int open_shm(size_t size) {
	key_t key = ftok(".", 'a');

	if (0 > key) {
		perror("ftok");
		return -1;
	}

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
			printf("delete shm successfully.\n");
		}
	}else {
		printf("delete shm failedly because the number of nattche is NONZERO.\n");
	}
	return 0;
}

void handler(int sig) {
	printf("%s : %d\n", __func__, sig);
}

int main() {
	
	//signal(SIGSEGV, handler);
	//open shm
	int shmid = open_shm(1024);

	if (0 > shmid) {
		return -1;
	}

	//map
	int *const pint = shmat(shmid, NULL, 0);
	if (NULL == pint) {
		printf("shmat fail");
		return -1;
	}else {
		printf("map successfully.\n");
	}

	int *p = pint;

	*p++ = 123;
	*p++ = 456;
	*p = 789;

	//umap
	shmdt(pint);
	//del_shm
	//del_shm(shmid);
	return 0;
}
