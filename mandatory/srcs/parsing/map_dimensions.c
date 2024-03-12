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

static int	trim_end_space(t_parsing *parsing, char *str)
{
	int		len;

	len = ft_strlen(str);
	while (len > 0 && ft_isspace(str[len - 1]))
	{
		str[len - 1] = '\0';
		len--;
	}
	if (len == 0)
		return (0);
	parsing->map_width += (len - parsing->map_width) \
		* (len > parsing->map_width);
	return (1);
}

static inline t_vdmnode	*iterate_remove_empty(t_parsing *parsing, \
	t_vdmnode *node)
{
	t_vdmnode	*save;

	while (node && is_only_spaces((char *)(node->data)))
	{
		save = node->next;
		vdmlist_del_node(parsing->list, node, free);
		node = save;
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
	while (node && trim_end_space(parsing, (char *)(node->data)))
		node = node->next;
	node = iterate_remove_empty(parsing, node);
	if (node)
		return (error_msg_int(\
			"cub3d: unknown/doubled texture and/or map is not contiguous\n", \
			STDERR_FILENO, 0));
	parsing->map_height = parsing->list->len;
	parsing->map_len = parsing->map_height * parsing->map_width;
	return (1);
}
