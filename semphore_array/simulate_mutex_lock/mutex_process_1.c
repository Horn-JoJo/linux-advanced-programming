#include<stdio.h>
#include<sys/types.h>
#include<sys/sem.h>
#include<sys/ipc.h>
#include<errno.h>
#include<stdlib.h>
#include<signal.h>

int set_value_semarray(int semarray_id, int pos_idx, int value) {
	if (0 > semctl(semarray_id, pos_idx, SETVAL, value)) {
		perror("semctl");
		return -1;
	}
	return 0;
}

int open_semarray(int nums){
	key_t key = ftok(".", 'a');
	if (0 > key) {
		perror("ftok");
		return -1;
	}

	int semarray_id = semget(key, nums, IPC_CREAT | IPC_EXCL | 0666);
	if (0 > semarray_id) {
		if (EEXIST == errno) {
			semarray_id = semget(key, nums, 0666);
			if (0 <= semarray_id) {
				printf("open semarray successfully.\n");
				return semarray_id;
			}else {
				perror("semget-open");
				return -1;
			}
		}
		perror("semget-creat");
		return -1;
	}
	set_value_semarray(semarray_id, 0, 1);
	printf("creat semarray successfully.\n");
	return semarray_id;
}


int del_semarray(int semarray_id) {
	if (0 > semctl(semarray_id, 0, IPC_RMID)) {
		perror("semctl-del_semarray");
		return -1;
	}
	printf("del_semarray successfully.\n");
	return 0;
}

int lock(int semarray_id) {
	struct sembuf op = {
		.sem_num = 0,
		.sem_op = -1,
		.sem_flg = SEM_UNDO,
	};

	if (0 > semop(semarray_id, &op, 1)) {
		perror("setop-simulate_lock");
		return -1;
	}
	return 0;
}


int unlock(int semarray_id) {
	struct sembuf op = {
		.sem_num = 0,
		.sem_op = 1,
		.sem_flg = SEM_UNDO,
	};

	if (0 > semop(semarray_id, &op, 1)) {
		perror("semop-simulate_unlock");
		return -1;
	}
	return 0;
}

int id = -1;
void handler(int sig) {
	del_semarray(id);
	exit(0);
}

int main() {
	signal(SIGINT, handler);
	//create and init lock
	id = open_semarray(1);
	if (0 > id) {
		printf("open_semarray failedly\n");
		return -1;
	}
	
	while(1) {
		lock(id);
		printf("\nprocess a lock successfully.\n");
		printf("PID[%d]  is using common resources.\n", getpid());
		unlock(id);
		printf("process a unlock successfully.\n");
		sleep(1);
	}

	return 0;
}
