#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<errno.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

int init_sem_arr(int sem_arr_id){
	//set a = 1
	if (0 > semctl(sem_arr_id, 0, SETVAL, 1)) {
		perror("semctl a");
		return -1;
	}
	//set b = 0
	if (0 > semctl(sem_arr_id, 1, SETVAL, 0)) {
		perror("semctl b");
		return -1;
	}
	return 0;
}

int open_sem_arr(int num) {
	key_t key = ftok(".", 'a');
	if (0 > key) {
		perror("ftok");
		return -1;
	}

	int sem_arr_id = semget(key, num, IPC_CREAT | IPC_EXCL | 0666);
	if (0 > sem_arr_id) {
		if (EEXIST == errno) {
			sem_arr_id = semget(key, num, 0666);
			if (0 <= sem_arr_id) {
				printf("open_sem_arr successfully.\n");
				return sem_arr_id;
			}else {
				printf("fail to open_sem_arr.\n");
				return -1;
			}
		}
		printf("fail to creat sem_array.\n");
		return -1;
	}
	printf("creat sem_array successfully.\n");
	init_sem_arr(sem_arr_id);
	return sem_arr_id;
}


int Pa(int sem_arr_id) {
	struct sembuf op = {
		.sem_num = 0,
		.sem_op = -1,
		.sem_flg = SEM_UNDO,
	};

	if (0 > semop(sem_arr_id, &op, 1)) {
		perror("setop-Pa");
		return -1;
	}
	return 0;
}


int Va(int sem_arr_id) {
	struct sembuf op = {
		.sem_num = 0,
		.sem_op = 1,
		.sem_flg = SEM_UNDO,
	};

	if (0 > semop(sem_arr_id, &op, 1)) {
		perror("semop-Va");
	}

}

int Pb(int sem_arr_id) {
	struct sembuf op = {
		.sem_num = 1,
		.sem_op = -1,
		.sem_flg = SEM_UNDO,
	};

	if (0 > semop(sem_arr_id, &op, 1)) {
		perror("setop-Pb");
		return -1;
	}
	return 0;
}


int Vb(int sem_arr_id) {
	struct sembuf op = {
		.sem_num = 1,
		.sem_op = 1,
		.sem_flg = SEM_UNDO,
	};

	if (0 > semop(sem_arr_id, &op, 1)) {
		perror("semop-Vb");
	}

}

int del_sem_arr(int sem_arr_id) {
	if (0 > semctl(sem_arr_id, 0, IPC_RMID)) {
		perror("semctl");
		return -1;
	}
	printf("delete sem_array successfully.\n");
	return 0;
}


int id = -1;
void handler(){
	del_sem_arr(id);
	exit(0);
}

int main() {
	
	id = open_sem_arr(2);
	if (0 > id) {
		return -1;
	}

	signal(SIGINT, handler);

	int i = 0;
	while(1) {
		if (0 > Pa(id)) {
			break;
		}
		printf("-------------maker:%d--------------\n", i++);
		sleep(1);
		if (0 > Vb(id)) {
			break;
		}
	}
	return 0;
}
