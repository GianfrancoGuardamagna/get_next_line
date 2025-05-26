/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:00:00 by gguardam          #+#    #+#             */
/*   Updated: 2025/05/22 10:00:00 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_buffer(int fd, char *saved)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!gnl_strchr(saved, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		saved = gnl_strjoin(saved, buffer);
	}
	free(buffer);
	return (saved);
}

static char	*extract_line(char *saved)
{
	int		i;
	char	*line;

	i = 0;
	if (!saved[i])
		return (NULL);
	while (saved[i] && saved[i] != '\n')
		i++;
	line = malloc(i + 2);
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
	new_saved = malloc(gnl_strlen(saved) - i + 1);
	if (!new_saved)
		return (NULL);
	i++;
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
	static char	*saved;

	if (fd < 2 || BUFFER_SIZE <= 0)
		return (NULL);
	saved = read_buffer(fd, saved);
	if (!saved)
		return (NULL);
	line = extract_line(saved);
	saved = update_saved(saved);
	return (line);
}