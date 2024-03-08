/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet_rest.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 19:19:25 by marvin            #+#    #+#             */
/*   Updated: 2024/02/27 19:19:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static inline void	setup_bullet_ray(t_ray *ray, t_bullet *bullet)
{
	ray->start = (t_vec2d){bullet->posi.x, bullet->posi.y};
	ray->ray_dir = (t_vec2d){bullet->dir.x, bullet->dir.y};
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
}

static inline void	move_ray(t_ray *ray)
{
	if (ray->first.x < ray->first.y)
	{
		ray->player_sqr.x += ray->axis_move.x;
		ray->first.x += ray->step.x;
		ray->side = 0;
	}
	else
	{
		ray->player_sqr.y += ray->axis_move.y;
		ray->first.y += ray->step.y;
		ray->side = 1;
	}
}

static inline void	calc_hit_and_dist(t_ray *ray, t_bullet *bullet, \
					float *wall_dist, t_vec2d *wall_hit)
{
	if (ray->side == 0)
	{
		*wall_dist = (ray->first.x - ray->step.x);
		wall_hit->y = bullet->posi.y + *wall_dist * ray->ray_dir.y;
		wall_hit->x = ray->player_sqr.x + (ray->player_sqr.x <= bullet->posi.x);
	}
	else
	{
		*wall_dist = (ray->first.y - ray->step.y);
		wall_hit->x = bullet->posi.x + *wall_dist * ray->ray_dir.x;
		wall_hit->y = ray->player_sqr.y + (ray->player_sqr.y <= bullet->posi.y);
	}
}

static inline t_vec3d	bullet_check_wall_hit(t_ray *ray, t_bullet *bullet)
{
	t_vec3d		res;
	t_vec2d		wall_hit;
	float		wall_dist;
	float		z;
	t_vec2d		floor_ceil;

	calc_hit_and_dist(ray, bullet, &wall_dist, &wall_hit);
	z = vec3d_get_z_from_xy(bullet->posi, bullet->dir, wall_hit);
	if (z < 0 || z > 1)
	{
		z = float_clamp(z, 0.0f, 1.0f);
		floor_ceil = vec3d_get_xy_from_z(bullet->posi, bullet->dir, z);
		bullet->wall_hole = false;
		res = (t_vec3d){floor_ceil.x, floor_ceil.y, z};
	}
	else
		res = (t_vec3d){wall_hit.x, wall_hit.y, z};
	return (res);
}

t_vec3d	bullet_rest(t_game *game, t_bullet *bullet)
{
	t_ray		ray;
	int			map_index;

	setup_bullet_ray(&ray, bullet);
	while (1)
	{
		move_ray(&ray);
		map_index = (int)ray.player_sqr.x \
		+ (int)ray.player_sqr.y * game->map.width;
		if (game->map.map[map_index] == MAP_WALL)
			return (bullet_check_wall_hit(&ray, bullet));
	}
}
