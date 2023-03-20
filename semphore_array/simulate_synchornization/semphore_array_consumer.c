#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<errno.h>
#include<unistd.h>

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

	int sem_arr_id = semget(key, num, 0666);
	if (0 <= sem_arr_id) {
		printf("open_sem_arr successfully.\n");
	}else {
		printf("fail to open_sem_arr.\n");
		return -1;
	}
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
		return -1;
	}
	return 0;
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
		return -1;
	}
	return 0;
}

int del_sem_arr(int sem_arr_id) {
	if (0 > semctl(sem_arr_id, 0, IPC_RMID)) {
		perror("semctl");
		return -1;
	}
	printf("delete sem_array successfully.\n");
	return 0;
}



int main() {

	int id = open_sem_arr(2);
	if (0 > id) {
		return -1;
	}

	int i = 0;
	while(1) {
		if (0 > Pb(id)) {
			break;
		}
		//delay 1 second in order to kill it 
		//where the opeareation PV can not finish
		//otherwise, can not make stuck.
		sleep(1);
		printf("-------------consumer:%d--------------\n", i++);
		if (0 > Va(id)) {
			break;
		}
	}
	return 0;
}
