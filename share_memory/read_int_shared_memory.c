#include<stdio.h>
#include<sys/shm.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<errno.h>

int open_shm(size_t size) {

	key_t key = ftok(".", 'a');
	if (0 > key) {
		perror("ftok");
		return -1;
	}

	int shmid = shmget(key, size, IPC_CREAT | IPC_EXCL | 0666);
	if (0 > shmid) {
		if (EEXIST == errno) {
			shmid = shmget(key, size, 0666);
			if (0 < shmid) {
				printf("open shm success!\n");
				return shmid;
			}
		}
		perror("shmget");
		return -1;
	}
	printf("create shm success!\n");
	return shmid;
}

int del_shm(int shmid) {
	struct shmid_ds s;
	if (0 > shmctl(shmid, IPC_STAT, &s)) {
		perror("shmctl");
		return -1;
	}

	if (0 == s.shm_nattch) {
		if (0 > shmctl(shmid, IPC_RMID, NULL)){
			perror("shmctl");
			return -1;
		}else {
			printf("delete shared memory successfully!\n");
		}
	}else {
		printf("delete shared memory failly\n.");
	}
	return 0;
}

int main() {
	
	//1.open shm
	int shmid = open_shm(1024);
	if (0 > shmid) {
		return -1;
	}

	//2.map
	int *pint = shmat(shmid, NULL, SHM_RDONLY);

	int *p = pint;
	while(*p == 0){
		sleep(3);
		printf("waiting write port to write int data.\n");
	}
	//read
	printf("nuber:%d\n", *p++);
	printf("nuber:%d\n", *p++);
	printf("nuber:%d\n", *p++);

	//3.umap
	shmdt(pint);

	//4.del shm
	del_shm(shmid);

	return 0;
}
