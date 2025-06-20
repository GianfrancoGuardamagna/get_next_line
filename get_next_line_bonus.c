/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:00:00 by gguardam          #+#    #+#             */
/*   Updated: 2025/06/20 17:18:13 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_buffer(int fd, char *saved)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = 1;
	while (!gnl_strchr_bonus(saved, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(buffer);
			if (saved)
				free(saved);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		saved = gnl_strjoin_bonus(saved, buffer);
	}
	free(buffer);
	return (saved);
}

static char	*extract_line(char *saved)
{
	int		i;
	char	*line;

	i = 0;
	if (!saved || !saved[i])
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

	if (!saved)
		return (NULL);
	i = 0;
	while (saved[i] && saved[i] != '\n')
		i++;
	if (!saved[i])
	{
		free(saved);
		return (NULL);
	}
	new_saved = malloc(gnl_strlen_bonus(saved) - i + 1);
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
	static char	*saved[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved[fd] = read_buffer(fd, saved[fd]);
	if (!saved[fd])
		return (NULL);
	line = extract_line(saved[fd]);
	saved[fd] = update_saved(saved[fd]);
	return (line);
}
