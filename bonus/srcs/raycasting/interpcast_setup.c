/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpcast_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:13:43 by marvin            #+#    #+#             */
/*   Updated: 2024/03/11 13:40:03 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	setup_orientation(t_game *game, t_sprite *sprite, t_interp_cast *cast);

static inline void	swap_cast_point(t_cast_point *first, t_cast_point *second)
{
	t_cast_point	point;

	point = *first;
	*first = *second;
	*second = point;
}

static void	setup_cast_point(t_game *game, t_interp_cast *cast, \
	t_sprite *sprite, t_cast_point *point)
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
	point->height = abs((int)(cast->h * sprite->height \
		/ (point->trans.y)));
	point->z_mod = (0.5f - sprite->height / 2 - sprite->cur_z \
		+ sprite->height / 2 * (sprite->type == BULLET));
	point->total_z_mod = cast->pitch_mod -(int)(((cast->play_z_mod \
		+ point->z_mod) * cast->h - cast->h / 2) / point->trans.y);
	point->min_screen_y = -point->height / 2 + point->total_z_mod;
	point->max_screen_y = point->height / 2 + point->total_z_mod;
	point->shade = ft_fabs(point->trans.y / game->max_vis_dist \
		* game->player.cur_dir_len / game->player.base_dir_len);
}

static inline void	setup_interp_cast_cont(t_interp_cast *cast)
{
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

int	setup_interp_cast(t_game *game, t_sprite *sprite, t_interp_cast *cast)
{
	cast->w = game->win.width;
	cast->h = game->win.height;
	cast->dir = vec2d_multi(game->player.dir_vec, game->player.cur_dir_len);
	setup_orientation(game, sprite, cast);
	cast->inv_cam = 1.0 / (game->player.plane.x * cast->dir.y \
		- game->player.plane.y * cast->dir.x);
	cast->pitch_mod = cast->h / 2 + game->player.pitch;
	cast->play_z_mod = ((game->player.cur_z + game->player.jump_z_mod \
		+ game->player.walk_z_mod));
	setup_cast_point(game, cast, sprite, &cast->start);
	setup_cast_point(game, cast, sprite, &cast->end);
	if (cast->start.screen_x > cast->end.screen_x)
		swap_cast_point(&cast->start, &cast->end);
	if (cast->start.trans.y < 0 && cast->end.trans.y < 0)
		return (0);
	setup_interp_cast_cont(cast);
	return (1);
}
