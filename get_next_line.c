/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:49:07 by gguardam          #+#    #+#             */
/*   Updated: 2025/07/05 15:43:21 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	new_saved = ft_calloc((ft_strlen(saved) - i + 1), sizeof(char));
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
	static char	*saved;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	saved = read_from_fd(fd, saved);
	if (!saved)
		return (NULL);
	line = extract_line(saved);
	saved = update_saved(saved);
	return (line);
}
