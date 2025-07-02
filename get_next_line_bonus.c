#include "get_next_line_bonus.h"

static char	*read_from_fd(int fd, char *backup)
{
	int		bytes_read;
	char	*buff;

	buff = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	bytes_read = 1;
	while ((!(ft_strchr(backup, '\n')) && bytes_read != 0))
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buff);
			free(backup);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		backup = ft_strjoin(backup, buff);
	}
	free(buff);
	return (backup);
}

static char	*get_line(char *backup)
{
	int		i;
	char	*line;

	i = 0;
	if (!backup || ! backup[i])
		return (NULL);
	while (backup[i] && backup[i] != '\n')
		i++;
	line = ft_calloc(sizeof(char), (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (backup[i] && backup[i] != '\n')
	{
		line[i] = backup[i];
		i++;
	}
	if (backup[i] == '\n')
	{
		line[i] = backup[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*update_backup(char *backup)
{
	int		i;
	int		j;
	char	*new_backup;

	i = 0;
	while (backup[i] && backup[i] != '\n')
		i++;
	if (!backup[i])
	{
		free(backup);
		return (NULL);
	}
	new_backup = malloc(sizeof(char) * (ft_strlen(backup) - i + 1));
	if (!new_backup)
	{
		free(backup);
		return (NULL);
	}
	++i;
	j = 0;
	while (backup[i])
		new_backup[j++] = backup[i++];
	new_backup[j] = '\0';
	free(backup);
	return (new_backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*backup[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!backup[fd])
	{
		backup[fd] = malloc(1);
		backup[fd][0] = '\0';
	}
	backup[fd] = read_from_fd(fd, backup[fd]);
	if (!backup[fd])
		return (NULL);
	line = get_line(backup[fd]);
	backup[fd] = update_backup(backup[fd]);
	return (line);
}
