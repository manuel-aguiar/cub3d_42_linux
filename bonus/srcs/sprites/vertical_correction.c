/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_correction.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:11:11 by marvin            #+#    #+#             */
/*   Updated: 2024/03/11 13:42:24 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static inline void	setup_correction_ray_cont(t_ray *ray)
{
	ray->player_sqr = (t_vec2d){(float)((int)ray->start.x), \
		(float)((int)ray->start.y)};
	ray->first.x = float_ternary(ray->ray_dir.x < 0, \
		(ray->start.x - ray->player_sqr.x), \
		((ray->player_sqr.x + 1) - ray->start.x));
	ray->first.y = float_ternary(ray->ray_dir.y < 0, \
		(ray->start.y - ray->player_sqr.y), \
		((ray->player_sqr.y + 1) - ray->start.y));
	ray->first = vec2d_product(ray->first, ray->step);
	ray->axis_move.x = ft_ternary(ray->ray_dir.x < 0, -1, 1);
	ray->axis_move.y = ft_ternary(ray->ray_dir.y < 0, -1, 1);
}

static inline void	setup_correction_ray(t_game *game, t_ray *ray)
{
	ray->w = game->win.width;
	ray->h = game->win.height;
	ray->dir_vec = vec2d_multi(game->player.dir_vec, \
		game->player.cur_dir_len);
	ray->plane = game->player.plane;
	ray->start = game->player.map_posi;
	ray->pitch_mod = ray->h / 2 + game->player.pitch;
	ray->z_mod = (game->player.cur_z + game->player.jump_z_mod + \
		game->player.walk_z_mod) * ray->h - ray->h / 2;
	ray->ray_dir = ray->dir_vec;
	ray->step.x = float_ternary(ray->ray_dir.x == 0, FLT_MAX, \
		ft_fabs(1.0f / ray->ray_dir.x));
	ray->step.y = float_ternary(ray->ray_dir.y == 0, FLT_MAX, \
		ft_fabs(1.0f / ray->ray_dir.y));
	setup_correction_ray_cont(ray);
}

static inline void	cast_this_ray(t_game *game, t_ray *ray)
{
	while (1)
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
		if (game->map.map[(int)ray->player_sqr.x \
		+ (int)ray->player_sqr.y * game->map.width] == MAP_WALL)
			break ;
	}
}

static t_vec2d	get_wall_hit_vertical(t_game *game, t_ray *ray)
{
	t_vec2d		wall_hit;
	float		wall_dist;

	if (ray->side == 0)
	{
		wall_dist = (ray->first.x - ray->step.x);
		wall_hit.y = game->player.map_posi.y + wall_dist * ray->ray_dir.y;
		wall_hit.x = ray->player_sqr.x + (ray->player_sqr.x \
			<= game->player.map_posi.x);
	}
	else
	{
		wall_dist = (ray->first.y - ray->step.y);
		wall_hit.x = game->player.map_posi.x + wall_dist * ray->ray_dir.x;
		wall_hit.y = ray->player_sqr.y + (ray->player_sqr.y \
			<= game->player.map_posi.y);
	}
	return (wall_hit);
}

float	vertical_coefficient(t_game *game)
{
	t_verti_coef	coef;

	setup_correction_ray(game, &coef.ray);
	cast_this_ray(game, &coef.ray);
	coef.wall_hit = get_wall_hit_vertical(game, &coef.ray);
	coef.hori.side = coef.ray.side;
	coef.hori.wall_dist = float_ternary(coef.ray.side == 0, \
		(coef.ray.first.x - coef.ray.step.x), \
		(coef.ray.first.y - coef.ray.step.y));
	coef.hori.line_h = (int)((coef.ray.h / coef.hori.wall_dist));
	coef.new_pitch = coef.hori.line_h / 2;
	coef.new_tan = coef.new_pitch * 2 / (float)game->win.height \
		* (float)game->player.base_dir_len \
		/ (float)game->player.cur_dir_len;
	coef.play_3d = (t_vec3d){game->player.map_posi.x, \
		game->player.map_posi.y, (game->player.cur_z \
		+ game->player.jump_z_mod + game->player.walk_z_mod)};
	coef.wall_3d = (t_vec3d){coef.wall_hit.x, coef.wall_hit.y, 1};
	coef.diff = vec3d_sub(coef.wall_3d, coef.play_3d);
	coef.times = float_ternary(ft_fabs(game->player.dir_vec.x) <= 0.001f, \
		coef.diff.y / game->player.dir_vec.y, coef.diff.x \
		/ game->player.dir_vec.x);
	coef.dir_z = coef.diff.z / coef.times;
	coef.coefficient = coef.dir_z / coef.new_tan;
	return (coef.coefficient);
}
