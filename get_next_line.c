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
	char buffer[BUFFER_SIZE];
	int in_buffer;
	// static char * temp;

	in_buffer = 0;
	in_buffer = read(fd, buffer, BUFFER_SIZE - 1);
	// temp = NULL;
	// printf("%d\n", in_buffer); //Devuelve longitud de cadena sin el '\0', que a su vez se puede utilizar como posicion del string
	// buffer[in_buffer] = '\0';
	// printf("%s\n", temp);
	if(buffer[in_buffer] != '\0')
	{
		printf("%s\n", buffer);
		// temp += strdup(buffer);
		get_next_line(fd);
	}
	else
	{
		// printf("%s\n", temp);
	}
	return ("c");
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

    doc = get_next_line(fd);

    close(fd);
    return 0;
}