/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file_to_list.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:47:12 by marvin            #+#    #+#             */
/*   Updated: 2024/02/22 20:47:12 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static inline int	open_file_prep_parsing(t_parsing *parsing)
{
	parsing->file_len = ft_strlen(parsing->file);
	if (parsing->file_len < 4 \
	|| ft_strncmp(&parsing->file[parsing->file_len - 4], ".cub", 4))
		return (error_msg_int("cub3d: file format is invalid", \
		STDERR_FILENO, 0));
	parsing->fd = open(parsing->file, O_RDONLY);
	if (parsing->fd == -1)
		return (perror_msg_int("open", 0));
	parsing->list = vdmlist_new();
	if (!parsing->list)
		return (0);
	return (1);
}

int	file_to_list(t_parsing *parsing)
{
	if (!open_file_prep_parsing(parsing))
		return (0);
	while (1)
	{
		parsing->gnl = get_next_line_len(parsing->fd);
		if (!parsing->gnl)
		{
			close(parsing->fd);
			return (0);
		}
		if (parsing->gnl->line)
			vdmlist_in_tail(parsing->list, parsing->gnl);
		else
		{
			free_gnl_len(parsing->gnl);
			break ;
		}
	}
	close(parsing->fd);
	return (1);
}

int	list_to_map(t_parsing *parsing)
{
	int			i;
	t_gnl_len	*gnl;

	parsing->map = malloc(sizeof(*(parsing->map)) \
		* parsing->map_height * parsing->map_width);
	if (!parsing->map)
		return (perror_msg_int("malloc", 0));
	i = 0;
	while (parsing->list->tail)
	{
		gnl = (t_gnl_len *)parsing->list->tail->data;
		ft_memcpy(&parsing->map[i * parsing->map_width], gnl->line, gnl->len);
		ft_memset(&parsing->map[i * parsing->map_width + gnl->len], \
			' ', parsing->map_width - gnl->len);
		vdmlist_del_tail(parsing->list, free_gnl_len);
		i++;
	}
	vdmlist_destroy(&parsing->list, free_gnl_len);
	return (1);
}
