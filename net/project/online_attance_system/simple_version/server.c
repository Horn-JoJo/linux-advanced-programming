#include<stdio.h>
#include<time.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>

#define err_log(log)\
	do{\
		perror(log);\
		exit(1);\
	}while(0)
#define MAXSIZE 1024
char msg[MAXSIZE];
char recvbuf[MAXSIZE / 4];

typedef struct sockaddr SA;

int main(int argc, const char *argv[])
{
	if (3 > argc)
	{
		fprintf(stderr, "SERVERAPP:%s IP PORT.\n", argv[0]);
		return -1;
	}
	
	int listenfd, confd;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (0 > listenfd) err_log("socket");

	struct sockaddr_in seraddr, cliaddr;
	socklen_t addlen = sizeof(seraddr);

	seraddr.sin_family = AF_INET;
	seraddr.sin_port = htons(atoi(argv[2]));
	seraddr.sin_addr.s_addr = inet_addr(argv[1]);

	if (0 > bind(listenfd, (SA *)&seraddr, addlen)) err_log("bind");

	if (0 > listen(listenfd, 20)) err_log("listen");


	FILE *fp = fopen("data", "a+");
	if (NULL == fp) err_log("fopen");	

	while (1)
	{
		printf("waiting to be connected...\n");
		confd = accept(listenfd, (SA *)&cliaddr, &addlen);
		if (0 > confd) err_log("accept");

		size_t sizes = recv(confd, recvbuf, MAXSIZE / 4, 0);
		if (0 > sizes) err_log("recv");

		time_t t= time(NULL);
		struct tm *p = localtime(&t);
		snprintf(msg, MAXSIZE,"{[IP:%s];[NAME:%s];[LOGTIME:%04d-%02d-%02d-%02d:%02d:%02d]}\n", inet_ntoa(cliaddr.sin_addr), recvbuf,
				p->tm_year + 1900, p->tm_mon + 1, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec);

		//printf("%s", msg);
		int len = strlen(msg);
		if (len != fwrite(msg, sizeof(char), len, fp))
		{
			perror("fwrite");
			fclose(fp);
			return -1;
		}
		printf("write msg to file done.\n");
		fflush(fp);

		if (0 == sizes)
		{
			printf("client exit");
			close(confd);
		}
	}
	fclose(fp);
	close(listenfd);
	return 0;
}
