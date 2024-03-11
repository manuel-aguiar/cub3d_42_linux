/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_collision_corners.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 14:47:40 by codespace         #+#    #+#             */
/*   Updated: 2024/03/11 13:40:34 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ray_to_nearest(t_move_colli *colli, t_vec2d *posi)
{
	colli->ray_to_nearest = vec2d_sub(colli->nearest, *posi);
	colli->ray_length = vec2d_len(colli->ray_to_nearest);
	colli->overlap = colli->unit_size - colli->ray_length;
	if (colli->overlap > 0)
	{
		colli->ray_to_nearest = vec2d_norm(colli->ray_to_nearest, \
			colli->ray_length);
		*posi = vec2d_sub(*posi, vec2d_multi(colli->ray_to_nearest, \
			colli->overlap));
	}
}

void	top_corners(t_move_colli *colli, t_vec2d *posi)
{
	if (colli->map->map[(colli->fixed_x - 1) + (colli->fixed_y + 1) \
	* colli->map->width] == MAP_WALL)
	{
		colli->nearest.x = ft_fmin(posi->x, (float)colli->fixed_x);
		colli->nearest.y = ft_fmax(posi->y, (float)(colli->fixed_y + 1));
		ray_to_nearest(colli, posi);
	}
	if (colli->map->map[(colli->fixed_x + 1) + (colli->fixed_y + 1) \
	* colli->map->width] == MAP_WALL)
	{
		colli->nearest.x = ft_fmax(posi->x, (float)(colli->fixed_x + 1));
		colli->nearest.y = ft_fmax(posi->y, (float)(colli->fixed_y + 1));
		ray_to_nearest(colli, posi);
	}
}

void	bot_corners(t_move_colli *colli, t_vec2d *posi)
{
	if (colli->map->map[(colli->fixed_x - 1) + (colli->fixed_y - 1) \
	* colli->map->width] == MAP_WALL)
	{
		colli->nearest.x = ft_fmin(posi->x, (float)(colli->fixed_x));
		colli->nearest.y = ft_fmin(posi->y, (float)(colli->fixed_y));
		ray_to_nearest(colli, posi);
	}
	if (colli->map->map[(colli->fixed_x + 1) + (colli->fixed_y - 1) \
	* colli->map->width] == MAP_WALL)
	{
		colli->nearest.x = ft_fmax(posi->x, (float)(colli->fixed_x + 1));
		colli->nearest.y = ft_fmin(posi->y, (float)(colli->fixed_y));
		ray_to_nearest(colli, posi);
	}
}
