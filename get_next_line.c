#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char *get_next_line(int fd)
{
	char	*buffer;
	int	bytes_read;

	buffer = malloc(sizeof(char) * 1024);
	if (!buffer)
		return (NULL);

	bytes_read = read(fd, buffer, 1023);
	if (bytes_read <= 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	printf("%s\n", buffer);
	return (buffer);
}

int	main(int argc, char **argv)
{
	int	fd;
	char	*line;

	if(argc != 2)
		printf("%s\n", "Only one file is allowed...");

	fd = open(argv[1], O_RDONLY);
	if(fd == -1)
		printf("%s\n", "Error while opening the file...");

	line = get_next_line(fd);
	if (line)
		free(line);
	close(fd);
	return (0);
}
