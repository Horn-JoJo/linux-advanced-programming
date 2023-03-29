#include<stdio.h>

int main(){
#if 0
	FILE *fp = (void *)0x100;//标准IO中需要开辟缓存放在内存中
	fclose(fp);//无效的地址没有缓存开辟，回收会段错误
#else 
	int fd = 10;//程序一运行起来系统会自动分配1024大小的数组用来存放文件运行
	//时信息,随便给定的是无效的
	if(0 > read(fd, 0, 0)){
		perror("read");

	}
	close(fd);//这里关闭本质就是设置该文件描述为无效，不涉及数组以及缓存的
	//回收等操作
#endif
}
