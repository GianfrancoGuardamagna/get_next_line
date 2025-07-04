#include "get_next_line_bonus.h"

static char	*read_from_fd(int fd, char *saved)
{
	int		bytes_read;
	char	*buff;

	buff = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buff)
	{
		free(saved);
		return (NULL);
	}
	bytes_read = 1;
	while ((!(ft_strchr(saved, '\n')) && bytes_read != 0))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buff);
			free(saved);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		saved = ft_strjoin(saved, buff);
	}
	free(buff);
	return (saved);
}

static char	*extract_line(char *saved)
{
	int		i;
	char	*line;

	i = 0;
	if (!saved || ! saved[i])
		return (NULL);
	while (saved[i] && saved[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
	{
		line[i] = saved[i];
		i++;
	}
	if (saved[i] == '\n')
	{
		line[i] = saved[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_saved(char *saved)
{
	int		i;
	int		j;
	char	*new_saved;

	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	new_saved = malloc(sizeof(char) * (ft_strlen(saved) - i + 1));
	if (!new_saved)
	{
		free(saved);
		return (NULL);
	}
	++i;
	j = 0;
	while (saved[i])
		new_saved[j++] = saved[i++];
	new_saved[j] = '\0';
	free(saved);
	return (new_saved);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*saved[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved[fd] = read_from_fd(fd, saved[fd]);
	if (!saved[fd])
		return (NULL);
	line = extract_line(saved[fd]);
	saved[fd] = update_saved(saved[fd]);
	return (line);
}
