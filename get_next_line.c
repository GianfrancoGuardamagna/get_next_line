#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

char *get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];  // Buffer estático para mantener datos entre llamadas
    static int position = 0;          // Posición actual en el buffer
    static int bytes_in_buffer = 0;   // Cantidad de bytes actuales en el buffer
    
    char *line = NULL;                // Línea que vamos a devolver
    int line_size = 0;                // Tamaño actual de la línea
    char c;                           // Carácter actual
    
    // Continuamos leyendo hasta encontrar un \n o EOF
    while (1)
    {
        // Si necesitamos leer más datos
        if (position >= bytes_in_buffer)
        {
            position = 0;
            bytes_in_buffer = read(fd, buffer, BUFFER_SIZE);
            
            // Si no hay más datos para leer
            if (bytes_in_buffer <= 0)
            {
                // Si ya habíamos leído algo, lo devolvemos
                if (line_size > 0)
                    return line;
                // Si no, liberamos memoria y retornamos NULL
                free(line);
                return NULL;
            }
        }
        
        // Tomamos un carácter del buffer
        c = buffer[position++];
        
        // Ampliamos la línea para añadir el nuevo carácter
        char *temp = malloc(line_size + BUFFER_SIZE); // +1 para el carácter, +1 para \0
        if (!temp)
        {
            free(line);
            return NULL;
        }
        
        // Copiamos la línea existente al nuevo buffer
        if (line)
        {
            memcpy(temp, line, line_size);
            free(line);
        }
        
        // Añadimos el nuevo carácter
        temp[line_size++] = c;
        temp[line_size] = '\0';
        line = temp;
        
        // Si encontramos un salto de línea, terminamos
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
    
    // Leemos e imprimimos línea por línea
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);  // No añadimos \n porque la línea ya lo incluye
        free(line);
    }
    
    close(fd);
    return 0;
}