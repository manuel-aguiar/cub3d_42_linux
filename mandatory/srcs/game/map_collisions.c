/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player_collisions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:06:07 by marvin            #+#    #+#             */
/*   Updated: 2024/01/24 17:06:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/*
https://github.com/OneLoneCoder/Javidx9/blob
/master/PixelGameEngine/SmallerProjects/OneLoneCoder_PGE_CircleVsRect.cpp
*/

void	top_corners(t_move_colli *colli, t_vec2d *posi);
void	bot_corners(t_move_colli *colli, t_vec2d *posi);

void	check_perpendicular_walls(t_move_colli *colli, t_vec2d *posi)
{
	if (colli->map->map[(colli->fixed_x - 1) + colli->fixed_y \
	* colli->map->width] == MAP_WALL)
		posi->x = ft_fmax(posi->x, colli->fixed_x + (colli->unit_size));
	if (colli->map->map[(colli->fixed_x + 1) + colli->fixed_y \
	* colli->map->width] == MAP_WALL)
		posi->x = ft_fmin(posi->x, colli->fixed_x + 1 - (colli->unit_size));
	if (colli->map->map[colli->fixed_x + (colli->fixed_y + 1) \
	* colli->map->width] == MAP_WALL)
		posi->y = ft_fmin(posi->y, colli->fixed_y + 1 - (colli->unit_size));
	if (colli->map->map[colli->fixed_x + (colli->fixed_y - 1) \
	* colli->map->width] == MAP_WALL)
		posi->y = ft_fmax(posi->y, colli->fixed_y + (colli->unit_size));
}

void	handle_collisions(t_game *game, t_vec2d *posi, \
						t_vec2d potencial, float unit_size)
{
	int				i;
	t_move_colli	colli;

	colli.map = &game->map;
	colli.fixed_x = (int)posi->x;
	colli.fixed_y = (int)posi->y;
	colli.unit_size = unit_size;
	colli.potential_len = vec2d_len(potencial);
	colli.divide_potential = 1 + (int)(colli.potential_len / colli.unit_size);
	colli.add = vec2d_multi(potencial, (1 / (float)colli.divide_potential));
	i = 0;
	while (i < colli.divide_potential)
	{
		colli.player = *posi;
		*posi = vec2d_add(*posi, colli.add);
		check_perpendicular_walls(&colli, posi);
		top_corners(&colli, posi);
		bot_corners(&colli, posi);
		i++;
	}
}
