/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gguardam <gguardam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 12:48:06 by gguardam          #+#    #+#             */
/*   Updated: 2025/07/05 12:48:37 by gguardam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

//File opening and control
# include <fcntl.h>
//file I/O (read, close)
# include <unistd.h>
//Memory allocation (malloc, free)
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 256
# endif

size_t		ft_strlen(const char *str);
char		*ft_strjoin(char *s1, char *s2);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strchr(const char *s, int c);
char		*get_next_line(int fd);
char		*ft_strdup(const char *s);

#endif
