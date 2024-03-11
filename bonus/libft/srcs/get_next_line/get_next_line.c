/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 19:30:32 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/01/12 11:10:27 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

extern int	buffer_to_line(char *buf, char **line, int *line_len);
extern int	buffer_refill(int fd, char *buf, char **line);

char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	char		*line;
	int			line_len;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	line = NULL;
	line_len = 0;
	while (1)
	{
		if (buffer_to_line(buf, &line, &line_len))
			break ;
		if (!buffer_refill(fd, buf, &line))
			break ;
	}
	return (line);
}

char	*get_next_line_multi(int fd)
{
	static char	buf[FOPEN_MAX][BUFFER_SIZE + 1];
	char		*line;
	int			line_len;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	line = NULL;
	line_len = 0;
	while (1)
	{
		if (buffer_to_line(buf[fd], &line, &line_len))
			break ;
		if (!buffer_refill(fd, buf[fd], &line))
			break ;
	}
	return (line);
}
