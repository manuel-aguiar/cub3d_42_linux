/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doorcast_setup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:13:43 by marvin            #+#    #+#             */
/*   Updated: 2024/03/05 11:34:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static inline void	swap_door_point(t_door_point *first, t_door_point *second)
{
	t_door_point	point;

	point = *first;
	*first = *second;
	*second = point;
}

static inline void	door_orientation(t_game *game, t_sprite *sprite, \
	t_door_cast *cast)
{
	if (cast->door->orient == NS)
	{
		cast->inverted = false;
		cast->start.point = (t_vec2d){sprite->posi.x - 0.5f, sprite->posi.y};
		cast->end.point = (t_vec2d){sprite->posi.x + 0.5f, sprite->posi.y};
	}
	else
	{
		cast->inverted = true;
		cast->start.point = (t_vec2d){sprite->posi.x, sprite->posi.y - 0.5f};
		cast->end.point = (t_vec2d){sprite->posi.x, sprite->posi.y + 0.5f};
	}
	if ((cast->door->orient == NS \
	&& game->player.map_posi.y > cast->start.point.y) \
	|| (cast->door->orient == WE \
	&& game->player.map_posi.x > cast->start.point.x))
	{
		vec2d_swap(&cast->start.point, &cast->end.point);
		cast->inverted = !cast->inverted;
	}
}

static void	setup_door_point(t_game *game, t_door_cast *cast, \
	t_door_point *point)
{
	point->relative = vec2d_sub(point->point, game->player.map_posi);
	point->trans.x = (cast->dir.y * point->relative.x - cast->dir.x \
		* point->relative.y);
	point->trans.y = (-game->player.plane.y * point->relative.x \
		+ game->player.plane.x * point->relative.y);
	point->trans = vec2d_multi(point->trans, cast->inv_cam);
	point->screen_x = (int)((cast->w / 2) * (1 + point->trans.x \
		/ point->trans.y));
	if (point->trans.y < 0)
		point->screen_x = (int)((cast->w / 2) * (1 - point->trans.x \
			/ point->trans.y));
	point->height = abs((int)(cast->h * 1.0f / (point->trans.y)));
	point->min_screen_y = -point->height / 2 + cast->pitch_mod \
		-(int)(cast->play_z_mod / point->trans.y);
	point->max_screen_y = point->height / 2 + cast->pitch_mod \
		-(int)(cast->play_z_mod / point->trans.y);
	point->shade = ft_fabs(point->trans.y / game->max_vis_dist \
		* game->player.cur_dir_len / game->player.base_dir_len);
}

static inline void	setup_door_cast_cont(t_door_cast *cast)
{
	if (cast->start.screen_x > cast->end.screen_x)
		swap_door_point(&cast->start, &cast->end);
	cast->tex_pix_width = cast->end.screen_x - cast->start.screen_x;
	cast->step_tex_min_y = (float)(cast->end.min_screen_y \
		- cast->start.min_screen_y) / (float)(cast->tex_pix_width);
	cast->step_tex_max_y = (float)(cast->end.max_screen_y \
		- cast->start.max_screen_y) / (float)(cast->tex_pix_width);
	cast->shade_save_x = cast->start.screen_x;
	cast->tex_step_x = 1.0f * cast->tex->height / cast->tex_pix_width;
	cast->out_screen_x = (0 - cast->start.screen_x) \
		* (cast->start.screen_x < 0);
	cast->tex_exact_x = cast->tex_step_x * cast->out_screen_x;
	cast->pix_exact_min_y = cast->start.min_screen_y \
		+ cast->step_tex_min_y * cast->out_screen_x;
	cast->pix_exact_max_y = cast->start.max_screen_y \
		+ cast->step_tex_max_y * cast->out_screen_x;
}

int	setup_door_cast(t_game *game, t_sprite *sprite, t_door_cast *cast)
{
	cast->w = game->win.width;
	cast->h = game->win.height;
	cast->dir = vec2d_multi(game->player.dir_vec, game->player.cur_dir_len);
	cast->door = (t_door *)sprite->data;
	cast->tex = &game->tex[DOOR_TEX];
	door_orientation(game, sprite, cast);
	cast->inv_cam = 1.0 / (game->player.plane.x * cast->dir.y \
		- game->player.plane.y * cast->dir.x);
	cast->pitch_mod = cast->h / 2 + game->player.pitch;
	cast->play_z_mod = ((game->player.cur_z + game->player.jump_z_mod \
		+ game->player.walk_z_mod) * cast->h - cast->h / 2);
	setup_door_point(game, cast, &cast->start);
	setup_door_point(game, cast, &cast->end);
	if (cast->start.trans.y < 0 && cast->start.trans.y < 0)
		return (0);
	setup_door_cast_cont(cast);
	return (1);
}
