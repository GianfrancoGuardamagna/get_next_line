#include "get_next_line.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;

	(void)argc;
	(void)argv;
	fd = open("files/1char.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	if (line == NULL)
		printf("---//NULL\\---\n");
	close(fd);
	return (0);
}
