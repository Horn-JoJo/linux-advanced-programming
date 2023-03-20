#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>


int main(){
	int i = 0;
	pid_t pid = vfork();
	if(-1 == pid){
		perror("vfork");
	}else if(0 == pid){
		while(1){
			if(i > 10)
				break;
			printf("ppid :%u, cur_pid:%u, i = %d\n", getppid(), getpid(), ++i);
			sleep(1);
		}
	}else{
		/*while(1){
			if(i > 20)
				break;
			printf("ppid :%u, cur_pid:%u, i = %d\n", getppid(), getpid(), ++i);
			sleep(1);
		}*/
		int second = 5;
		while(second){
			printf("我还没崩，还能坚持%d s！！！\n", second);
			second--;
			sleep(1);
		}
		printf("完了，需要返回地址了，但子程序已经将返回地址弹出栈了，找不到了, 呜呜呜，game over!\n");
	}
	return 0;
}
