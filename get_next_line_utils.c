/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:00:00 by gguardam          #+#    #+#             */
/*   Updated: 2025/05/22 10:00:00 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gnl_strlen(const char *s)
{
	size_t	len;

	if (!s)
		return (0);
	len = 0;
	while (s[len])
		len++;
	return (len);
}

char	*gnl_strchr(const char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1 && !s2)
		return (NULL);
	result = malloc(gnl_strlen(s1 ? s1 : "") + gnl_strlen(s2 ? s2 : "") + 1);
	if (!result)
		return (NULL);
	i = 0;
	if (s1)
	{
		while (s1[i])
		{
			result[i] = s1[i];
			i++;
		}
	}
	j = 0;
	if (s2)
	{
		while (s2[j])
			result[i++] = s2[j++];
	}
	result[i] = '\0';
	if (s1)
		free(s1);
	return (result);
}
