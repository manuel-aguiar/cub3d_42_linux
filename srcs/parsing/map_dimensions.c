/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_dimensions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:51:05 by marvin            #+#    #+#             */
/*   Updated: 2024/02/22 20:51:05 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	trim_end_space(t_parsing *parsing, t_gnl_len *gnl)
{
	int		len;
	char	*str;

	len = gnl->len;
	str = gnl->line;
	len -= (str[len - 1] == '\n');
	gnl->len = len;
	while (len && str[len - 1] == ' ')
		len--;
	if (!len)
		return (0);
	gnl->len = len;
	parsing->map_width += (len - parsing->map_width) \
		* (len > parsing->map_width);
	return (1);
}

static inline t_vdmnode	*iterate_remove_empty(t_parsing *parsing, \
	t_vdmnode *node)
{
	t_vdmnode	*save;

	while (node && is_only_spaces(((t_gnl_len *)(node->data))->line))
	{
		save = node;
		vdmlist_del_node(parsing->list, node, free_gnl_len);
		node = save->next;
	}
	return (node);
}

int	get_map_dimensions(t_parsing *parsing)
{
	t_vdmnode	*node;

	node = parsing->list->head;
	node = iterate_remove_empty(parsing, node);
	if (!node)
		return (error_msg_int("cub3d: map is empty\n", STDERR_FILENO, 0));
	while (node && trim_end_space(parsing, (t_gnl_len *)(node->data)))
		node = node->next;
	node = iterate_remove_empty(parsing, node);
	if (node)
		return (error_msg_int("cub3d: file must end on map\n", \
			STDERR_FILENO, 0));
	parsing->map_height = parsing->list->len;
	return (1);
}
