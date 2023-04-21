#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>

typedef struct sockaddr_in SAI;
typedef struct sockaddr SA;

#define MAX 1024
char buf[MAX];

#define err_deal(log, ERR)\
	do{\
		perror(log);\
		goto ERR;\
	}while(0)

void handler(int sig)
{
	printf("timeout...........\n");
}

int main()
{

	int listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > listenfd) err_deal("socket", ERR);

	int on = 1;
	if (0 > setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on))) err_deal("setsockopt", ERR1);

	SAI srvaddr = {
		.sin_family = AF_INET,
		.sin_port = htons(9999),
		.sin_addr.s_addr = inet_addr("192.168.181.128")
	};

	SAI cliaddr;
	socklen_t addrlen = sizeof(cliaddr);

	if (0 > bind(listenfd, (SA *)&srvaddr, sizeof(srvaddr))) err_deal("bind", ERR1);
	if (0 > listen(listenfd, 15)) err_deal("listen", ERR1);

	struct sigaction act;
	sigaction(SIGALRM, NULL, &act);//获取原有内核的action状态
	act.sa_handler = handler;//注册触发该信号时需要回调函数来处理
	act.sa_flags &= ~SA_RESTART;//不重启
	sigaction(SIGALRM, &act, NULL);//登记到内核中

	while (1)
	{
		//alarm(1);
		int connfd = accept(listenfd, (SA *)&cliaddr, &addrlen);
		if (0 > connfd)
		{
			perror("accept");
			continue;
		}

		while (1)
		{
			alarm(1);
			int size = recv(connfd, buf, MAX, 0);
			if (0 > size)
			{
				perror("recv");
				continue;
			}
			else if (0 == size)
			{
				printf("peer exit...\n");
				break;
			}
			send(connfd, buf, size, 0);			
			printf("recv: %s\n", buf);
		}
		memset(buf, 0, sizeof(buf));
		close(connfd);
	}
	close(listenfd);

	return 0;
ERR1:
	close(listenfd);
ERR:
	return -1;
}
