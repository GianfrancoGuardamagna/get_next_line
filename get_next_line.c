#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

//ELIMINAR AL MOMENTO DE PRESENTAR
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	static int position;
	static int in_buffer;

	position = 0;
	in_buffer += read(fd, buffer, BUFFER_SIZE);
	
	return ('c');
}

int main(int argc, char **argv)
{
    int fd;
    char *doc;
    
    if (argc != 2)
    {
        printf("Only one file is allowed...\n");
        return 1;
    }
    fd = open(argv[1], O_RDONLY);
    if (fd == -1)
    {
        printf("Error while opening the file...\n");
        return 1;
    }
    while((doc = get_next_line(fd)) != 0)
	{
		printf("%s\n", doc);
		free(doc);
	}
    close(fd);
    return 0;
}