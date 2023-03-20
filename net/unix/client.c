#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <string.h>
#include <unistd.h>

typedef struct sockaddr_un SUN;
typedef struct sockaddr SA;

#define MAX 1024
char sndbuf[MAX];
char rcvbuf[MAX];

#define err_deal_with(err_log, ORDER)\
	do{\
		perror(err_log);\
		goto ORDER;\
	}while(0)

int main()
{
	int connfd = socket(AF_LOCAL, SOCK_STREAM, 0);
	if (0 > connfd) err_deal_with("socket", ERR);

	
	SUN srvaddr;
	memset(&srvaddr, 0, sizeof(srvaddr));
	srvaddr.sun_family = AF_LOCAL;
	strcpy(srvaddr.sun_path, "mysocket");

	if (0 > connect(connfd, (SA *)&srvaddr, sizeof(srvaddr))) err_deal_with("connect", ERR1);

	while (1)
	{
		fgets(sndbuf, MAX, stdin);
		sndbuf[strlen(sndbuf) - 1] = 0;
		if (strncmp(sndbuf, "quit", 4) == 0) break;
		if (0 > send(connfd, sndbuf, strlen(sndbuf), 0))
		{
			perror("send");
			break;
		}
		recv(connfd, rcvbuf, sizeof(rcvbuf), 0);
		puts(rcvbuf);

		memset(sndbuf, 0, sizeof(sndbuf));
		memset(rcvbuf, 0, sizeof(rcvbuf));
	}

ERR1:
	close(connfd);
ERR:
	return 0;
}
