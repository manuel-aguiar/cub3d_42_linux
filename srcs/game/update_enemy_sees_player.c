/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_enemy_sees_player.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:44:53 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:40:25 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static inline void	setup_hit_ray(t_game *game, t_ray *ray, t_vec2d dir)
{
	ray->start = game->player.map_posi;
	ray->ray_dir = dir;
	ray->step.x = float_ternary(ray->ray_dir.x == 0, FLT_MAX, \
		ft_fabs(1.0f / ray->ray_dir.x));
	ray->step.y = float_ternary(ray->ray_dir.y == 0, FLT_MAX, \
		ft_fabs(1.0f / ray->ray_dir.y));
	ray->player_sqr = (t_vec2d){(float)((int)ray->start.x), \
		(float)((int)ray->start.y)};
	ray->first.x = float_ternary(ray->ray_dir.x < 0, \
		(ray->start.x - ray->player_sqr.x), \
				((ray->player_sqr.x + 1) - ray->start.x));
	ray->first.y = float_ternary(ray->ray_dir.y < 0, \
		(ray->start.y - ray->player_sqr.y), \
				((ray->player_sqr.y + 1) - ray->start.y));
	ray->first = vec2d_product(ray->first, ray->step);
	ray->side = !(ray->first.x < ray->first.y);
	ray->axis_move.x = ft_ternary(ray->ray_dir.x < 0, -1, 1);
	ray->axis_move.y = ft_ternary(ray->ray_dir.y < 0, -1, 1);
	ray->wall_dist = 0;
}

static inline void	move_ray(t_ray *ray)
{
	if (ray->first.x < ray->first.y)
	{
		ray->player_sqr.x += ray->axis_move.x;
		ray->first.x += ray->step.x;
		ray->side = 0;
		ray->wall_dist = (ray->first.x - ray->step.x);
	}
	else
	{
		ray->player_sqr.y += ray->axis_move.y;
		ray->first.y += ray->step.y;
		ray->side = 1;
		ray->wall_dist = (ray->first.y - ray->step.y);
	}
}

static int	door_blocks_view(t_game *game, t_sprite *sprite, int map_index)
{
	t_door	*door;

	door = ((t_door *)(game->map.doors[map_index]->data));
	if (door->state == DOOR_CLOSED)
	{
		if (door->orient == NS && \
		((sprite->posi.y > door->base_position.y \
		&& door->base_position.y > game->player.map_posi.y) || \
		(sprite->posi.y < door->base_position.y \
		&& door->base_position.y < game->player.map_posi.y)))
			return (1);
		if (door->orient == WE && \
		((sprite->posi.x > door->base_position.x \
		&& door->base_position.x > game->player.map_posi.x) || \
		(sprite->posi.x < door->base_position.x \
		&& door->base_position.x < game->player.map_posi.x)))
			return (1);
	}
	return (0);
}

int	enemy_sees_player(t_game *game, t_sprite *sprite, t_vec2d dir)
{
	t_ray	ray;
	int		map_index;

	setup_hit_ray(game, &ray, dir);
	while (1)
	{
		move_ray(&ray);
		map_index = (int)ray.player_sqr.x \
		+ (int)ray.player_sqr.y * game->map.width;
		if (game->map.map[map_index] == MAP_WALL \
		|| (game->map.map[map_index] == MAP_DOOR \
		&& door_blocks_view(game, sprite, map_index)))
			return (0);
		if ((int)ray.player_sqr.x == (int)sprite->posi.x \
		&& (int)ray.player_sqr.y == (int)sprite->posi.y)
			return (1);
	}
	return (1);
}
