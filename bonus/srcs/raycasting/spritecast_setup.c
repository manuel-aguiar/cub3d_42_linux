/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecast_setup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:55:29 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:47:04 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	setup_common_spritecast(t_game *game, t_sp_cast *cast)
{
	cast->win_w = game->win.width;
	cast->win_h = game->win.height;
	cast->play_posi = game->player.map_posi;
	cast->play_dir = vec2d_multi(game->player.dir_vec, \
		game->player.cur_dir_len);
	cast->play_plane = game->player.plane;
	cast->pitch_mod = game->player.pitch;
	cast->play_z_mod = game->player.cur_z + game->player.jump_z_mod \
		+ game->player.walk_z_mod;
	cast->inv_camera = 1.0f / (cast->play_plane.x * cast->play_dir.y \
		- cast->play_plane.y * cast->play_dir.x);
}

static inline void	setup_this_cont(t_game *game, t_sp_cast *cast)
{
	cast->bot_pix_y = cast->total_z_mod - cast->sp_pix_h / 2;
	cast->top_pix_y = cast->total_z_mod + cast->sp_pix_h / 2;
	cast->left_pix_x = cast->centre_pix_x - cast->sp_pix_w / 2;
	cast->right_pix_x = cast->centre_pix_x + cast->sp_pix_w / 2;
	cast->tex_step_x = cast->tex->height / (float)cast->sp_pix_w;
	cast->tex_step_y = cast->tex->width / (float)cast->sp_pix_h;
	cast->tex_exact_x = 0;
	cast->tex_exact_y = 0;
	cast->shade_wgt = cast->trans.y / (game->max_vis_dist \
		/ game->player.cur_dir_len * game->player.base_dir_len);
}

void	setup_this_spritecast(t_game *game, t_sp_cast *cast, int i)
{
	cast->sprite = game->sorted[i];
	cast->tex = &game->tex[cast->sprite->tex];
	cast->relative = vec2d_sub(cast->sprite->posi, cast->play_posi);
	cast->trans.x = (cast->play_dir.y * cast->relative.x \
		- cast->play_dir.x * cast->relative.y);
	cast->trans.y = (-cast->play_plane.y * cast->relative.x \
		+ cast->play_plane.x * cast->relative.y);
	cast->trans = vec2d_multi(cast->trans, cast->inv_camera);
	cast->sp_z_mod = (0.5f - cast->sprite->height / 2 \
		- cast->sprite->cur_z + cast->sprite->height / 2 \
		* (cast->sprite->type == BULLET));
	cast->centre_pix_x = (int)((cast->win_w / 2) * (1 + cast->trans.x \
		/ cast->trans.y));
	cast->sp_pix_h = ft_abs((int)(cast->win_h * cast->sprite->height \
		/ cast->trans.y));
	cast->sp_pix_w = ft_abs((int)(cast->win_w * cast->sprite->unit_size * 2 \
		/ cast->trans.y));
	cast->total_z_mod = cast->win_h / 2 + cast->pitch_mod \
		- (int)(((cast->play_z_mod + cast->sp_z_mod) * cast->win_h \
		- cast->win_h / 2) / cast->trans.y);
	setup_this_cont(game, cast);
}
