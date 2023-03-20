#include <stdio.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/select.h>
#include <unistd.h>

int main()
{
	int fd = open("/dev/input/mice", O_RDONLY);
	if (0 > fd)
	{
		perror("open");
		return -1;
	}

	int retval;
	char buf[1024] = {0};
	struct pollfd fds[2];
	fds[0].fd = 0;
	fds[0].events = POLLIN;
	fds[1].fd = fd;
	fds[1].events = POLLIN;

	while (1)
	{
		retval = poll(fds, 2, 1000);
		if (0 > retval)
		{
			perror("poll");
			break;
		}
		else if (0 == retval)
		{
			printf("timeout.....\n");
			continue;
		}
		else 
		{
			if (fds[0].revents & POLLIN)
			{
				printf("data from keyboard.\n");
				fgets(buf, 1024, stdin);
				fputs(buf, stdout);
			}

			if (fds[1].revents & POLLIN)
			{
				printf("data from mouse.\n");
				read(fd, buf, sizeof(buf));
			}
		}
	}
	close(fd);
	return 0;

}
