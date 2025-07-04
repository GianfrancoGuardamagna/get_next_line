#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd1;
	int		fd2;
	int		fd3;
	char	*line1;
	char	*line2;
	char	*line3;

	fd1 = open("files/1char.txt", O_RDONLY);
	// fd2 = open("files/cable.txt", O_RDONLY);
	// fd3 = open("files/desarma.txt", O_RDONLY);
	fd2 = open("ERROR", O_RDONLY);
	fd3 = open("ERROR", O_RDONLY);

	while (1)
	{
		line1 = get_next_line(fd1);
		line2 = get_next_line(fd2);
		line3 = get_next_line(fd3);

		if (!line1 && !line2 && !line3)
			break;

		if (line1)
		{
			printf("FD1: %s\n", line1);
			free(line1);
		}
		else if (line1 == NULL)
			printf("FD1: ---//NULL\\---\n");
		if (line2)
		{
			printf("FD2: %s\n", line2);
			free(line2);
		}
		else if (line2 == NULL)
			printf("FD2: ---//NULL\\---\n");
		if (line3)
		{
			printf("FD3: %s\n", line3);
			free(line3);
		}
		else if (line3 == NULL)
			printf("FD3: ---//NULL\\---\n");
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}
