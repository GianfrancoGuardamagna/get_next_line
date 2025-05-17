#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int position = 0;
    static int bytes_in_buffer = 0;
    
    char *line = NULL;
    int line_size = 0;
    char c;
    
    while (1)
    {
        if (position >= bytes_in_buffer)
        {
            position = 0;
            bytes_in_buffer = read(fd, buffer, BUFFER_SIZE); //Esto almacena cuanto buffer le hayamos pasado
            if (bytes_in_buffer <= 0)
            {
                if (line_size > 0)
                    return line;
                free(line);
                return NULL;
            }
        }
        c = buffer[position++];
        char *temp = malloc(line_size + BUFFER_SIZE);
        if (!temp)
        {
            free(line);
            return NULL;
        }
        
        if (line)
        {
            memcpy(temp, line, line_size);
            free(line);
        }
        
        temp[line_size++] = c;
        temp[line_size] = '\0';
        line = temp;
        
        if (c == '\n')
            return line;
    }
}

int main(int argc, char **argv)
{
    int fd;
    char *line;
    
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
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    
    close(fd);
    return 0;
}