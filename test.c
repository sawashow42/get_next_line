#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int fd, cl;
	char buff[30+1];
	int rc;

	fd = open("test.txt", O_RDONLY);
	printf("%d\n", fd);
	if (fd == -1)
	{
		printf("ファイルオープンエラー\n");
	}
	else{
		buff[rc] = '\0';
		printf("read:%d - %s\n", rc, buff);
	}
	//close(fd);
}