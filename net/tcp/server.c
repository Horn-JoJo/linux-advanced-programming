#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

#define err_log(log)\
	do{\
		perror(log);\
		exit(1);\
	}while(0)

typedef struct sockaddr SA;

#define MAXSIZE 64

int main(int argc, const char *argv[])
{
	if (3 > argc)
	{
		fprintf(stderr, "USER:%s IP PORT\n", argv[0]);
		return -1;
	}
	
	int listenfd , confd;
	size_t size;
	char buf[MAXSIZE] = {0};

	//创建硬件
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > listenfd) err_log("socket");

	//定义初始化地址
	struct sockaddr_in seraddr = {
		.sin_family = AF_INET,
		.sin_port = htons(atoi(argv[2])),
		.sin_addr.s_addr = inet_addr(argv[1])
	};

	//绑定硬件和地址
	if (0 > bind(listenfd, (SA *)&seraddr, sizeof(seraddr))) err_log("bind");
	
	//设置为监听套接字，等待队列长度为20
	if (0 > listen(listenfd, 20)) err_log("listen");

	while (1)
	{
		printf("waiting for connect...\n");
		//接收成功返回连接套接字
		confd = accept(listenfd, NULL, NULL);
		if (0 > confd) err_log("accept");
		
		//收从套接字来的数据到长度为MAXSIZE大小的数据，如果没有数据就阻塞等数据
		size = recv(confd, buf, MAXSIZE, 0);
		if (0 > size) err_log("recv");

		//puts(buf);
		fprintf(stdout, "client data: %s\n", buf);


		if (0 == size)
		{
			printf("client exit\n");
			close(confd);
		}
	}
	close(listenfd);
	return 0;
}
