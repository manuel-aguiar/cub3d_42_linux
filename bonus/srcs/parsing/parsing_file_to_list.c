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
		return (error_msg_int("cub3d: file format is invalid\n", \
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
		parsing->gnl = get_next_line(parsing->fd);
		if (parsing->gnl)
		{
			if (!vdmlist_in_tail(parsing->list, parsing->gnl))
			{
				close(parsing->fd);
				parsing->gnl = NULL;
				return (0);
			}
			parsing->gnl = NULL;
		}
		else
			break ;
	}
	close(parsing->fd);
	return (1);
}

int	list_to_map(t_parsing *parsing)
{
	int			i;
	char		*gnl;
	int			gnl_len;

	parsing->map = malloc(sizeof(*(parsing->map)) \
		* parsing->map_len);
	if (!parsing->map)
		return (perror_msg_int("malloc", 0));
	i = 0;
	while (parsing->list->tail)
	{
		gnl = (char *)parsing->list->tail->data;
		gnl_len = ft_strlen(gnl);
		ft_memcpy(&parsing->map[i * parsing->map_width], gnl, gnl_len);
		ft_memset(&parsing->map[i * parsing->map_width + gnl_len], \
			' ', parsing->map_width - gnl_len);
		vdmlist_del_tail(parsing->list, free);
		i++;
	}
	vdmlist_destroy(&parsing->list, free);
	return (1);
}
