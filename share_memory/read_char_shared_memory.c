#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<errno.h>
#include<sys/shm.h>
#include<unistd.h>

int open_shm(size_t size) {
	
	//acquire key value
	key_t key = ftok(".", 'a');
	if (0 > key) {
		perror("ftok");
		return -1;
	}

	//acquire id
	int shmid = shmget(key, size, IPC_EXCL | IPC_CREAT | 0666);
	if (0 > shmid) {
		if (EEXIST == errno) {
			shmid = shmget(key, size, 0666);
			if (0 < shmid) {
				printf("open shm successfully.\n");
				return shmid;
			}
		}
		perror("shmget");
		return -1;
	}

	printf("create shm successfully.\n");
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
	}else {
		printf("t.shm_nattch counter NOZERO!!!\n");
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
	char *p_shm = shmat(shmid, NULL, SHM_RDONLY);

	while(1){
		sleep(5);
		if(p_shm[0]) {
			break;
		}
		printf("waiting write port to write data......\n");
	}
	printf("The contex of p_shm:%s\n", p_shm);

	//unmap
	shmdt(p_shm);
	del_shm(shmid);

	return 0;
}
