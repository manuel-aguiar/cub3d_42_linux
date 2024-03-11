/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_funcs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:10:29 by marvin            #+#    #+#             */
/*   Updated: 2024/02/22 20:10:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	map_row(t_map *map, int index)
{
	return (index / map->width);
}

int	map_col(t_map *map, int index)
{
	return (index % map->width);
}

void	free_map(t_map *map)
{
	int	i;

	if (map->map)
		free(map->map);
	i = 0;
	while (i < NUM_TEX)
	{
		if (map->tex_data[i].path)
			free(map->tex_data[i].path);
		i++;
	}
}
