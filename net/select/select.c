#include <stdio.h>
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
	fd_set fds, rfds;
	FD_ZERO(&fds);
	FD_SET(0, &fds);
	FD_SET(fd, &fds);

	while (1)
	{
		rfds = fds;
		struct timeval tv = {1};
		retval = select(fd + 1, &rfds, NULL, NULL, &tv);
		if (0 > retval)
		{
			perror("select");
			break;
		}
		else if (0 == retval)
		{
			printf("timeout.....\n");
			continue;
		}
		else 
		{
			if (FD_ISSET(0, &rfds))
			{
				printf("data from keyboard.\n");
				read(0, buf, sizeof(buf));
			}

			if (FD_ISSET(fd, &rfds))
			{
				printf("data from mouse.\n");
				read(fd, buf, sizeof(buf));
			}
		}
	}
	close(fd);
	return 0;

}
