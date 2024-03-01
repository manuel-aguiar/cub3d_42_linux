/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 21:26:19 by marvin            #+#    #+#             */
/*   Updated: 2024/02/15 21:26:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	flood_fill(t_parsing *parse, int row, int col, char caller)
{
	char	me;
	bool	within_bounds;

	within_bounds = (row >= 0 && row < parse->map_height \
	&& col >= 0 && col < parse->map_width);
	if (within_bounds)
		me = parse->map_copy[row * parse->map_width + col];
	if ((within_bounds && me == FLOOD_CHAR))
		return ;
	if (caller != MAP_WALL && (!within_bounds || me == MAP_EMPTY))
	{
		parse->ff_found = true;
		return ;
	}
	if (!within_bounds || me == MAP_EMPTY)
		return ;
	parse->map_copy[row * parse->map_width + col] = FLOOD_CHAR;
	flood_fill(parse, row - 1, col - 1, me);
	flood_fill(parse, row - 0, col - 1, me);
	flood_fill(parse, row + 1, col - 1, me);
	flood_fill(parse, row - 0, col - 1, me);
	flood_fill(parse, row - 0, col + 1, me);
	flood_fill(parse, row - 1, col + 1, me);
	flood_fill(parse, row - 0, col + 1, me);
	flood_fill(parse, row + 1, col + 1, me);
}

int	flood_count_island(t_parsing *parse)
{
	int	i;

	parse->ff_found = false;
	parse->ff_count = 0;
	parse->map_copy = ft_memdup(parse->map, sizeof(*parse->map) * parse->map_height * parse->map_width);
	if (!parse->map_copy)
		return (perror_msg_int("malloc", 0));
	i = 0;
	while (parse->map_copy[i] == MAP_EMPTY)
		i++;
	if (i < parse->map_height * parse->map_width && parse->map_copy[i] == MAP_WALL)
		flood_fill(parse, i / parse->map_width, i % parse->map_width, MAP_WALL);
	else
	{
		free(parse->map_copy);
		return (error_msg_int("cub3d: bad map: not surrounded by walls\n", STDERR_FILENO, 0));
	}
	if (parse->ff_found == true)
	{
		free(parse->map_copy);
		return (error_msg_int("cub3d: bad map: not surrounded by walls\n", STDERR_FILENO, 0));
	}
	while (parse->map_copy[i] == MAP_EMPTY || parse->map_copy[i] == FLOOD_CHAR)
		i++;
	if (i < parse->map_height * parse->map_width)
	{
		free(parse->map_copy);
		return (error_msg_int("cub3d: bad map: multiple islands\n", STDERR_FILENO, 0));
	}
	free(parse->map_copy);
	return (1);
}
