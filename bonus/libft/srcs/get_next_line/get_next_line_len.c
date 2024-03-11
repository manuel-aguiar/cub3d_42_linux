/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_len.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:09:44 by marvin            #+#    #+#             */
/*   Updated: 2024/01/12 11:09:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

extern void	buffer_clean(char *buf, int pivot);
extern int	increase_line(char **new, char **old, int *old_size, int inc_size);

int	gnl_len_strncat(char *buf, int inc_size, t_gnl_len *gnl)
{
	char	*new_line;

	if (!increase_line(&new_line, &gnl->line, &gnl->len, inc_size))
	{
		gnl->status = GNL_FAILURE;
		return (0);
	}
	if (gnl->line)
	{
		ft_memcpy(new_line, gnl->line, gnl->len);
		free(gnl->line);
	}
	ft_memcpy(&new_line[gnl->len], buf, inc_size);
	gnl->len += inc_size;
	new_line[gnl->len] = '\0';
	gnl->line = new_line;
	return (1);
}

static int	gnl_len_buffer_to_line(char *buf, t_gnl_len *gnl)
{
	int	i;
	int	stop;

	if (!*buf)
		return (0);
	stop = 0;
	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		stop = 1;
	if (!gnl_len_strncat(buf, i + stop, gnl))
		stop = 1;
	buffer_clean(buf, i + 1);
	return (stop);
}

static int	gnl_len_buffer_refill(int fd, char *buf, t_gnl_len *gnl)
{
	int	bytes;

	bytes = read(fd, buf, BUFFER_SIZE);
	if (bytes < 0)
	{
		buf[0] = '\0';
		if (gnl->line)
			ft_free_set_null(&gnl->line);
		return (gnl->status = GNL_BAD_FD);
	}
	buf[bytes] = '\0';
	if (!bytes)
		return (gnl->status = GNL_EOF);
	return (GNL_OK);
}

t_gnl_len	*get_next_line_len(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	t_gnl_len	*gnl;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > FOPEN_MAX)
		return (NULL);
	gnl = malloc(sizeof(*gnl));
	if (!gnl)
		return (perror_msg_ptr("malloc", NULL));
	gnl->line = NULL;
	gnl->len = 0;
	gnl->status = GNL_OK;
	while (1)
	{
		if (gnl_len_buffer_to_line(buf, gnl))
			break ;
		if (gnl_len_buffer_refill(fd, buf, gnl) != GNL_OK)
			break ;
	}
	if (!gnl->line)
		gnl->len = -1;
	if (gnl->status == GNL_FAILURE)
		return (ft_free_set_null(&gnl));
	return (gnl);
}
