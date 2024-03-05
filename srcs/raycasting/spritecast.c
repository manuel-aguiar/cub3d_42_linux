/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_cast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 13:05:50 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 13:05:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"


void	print_sorted_sprites(t_game *game)
{
	int i;

	i = 0;
	while (i < game->sprite_count)
	{
		printf("sprite %d, dist %.10f, posi (%.3f, %.3f)", game->sprites[i].type, game->sprites[i].dist, game->sprites[i].posi.x, game->sprites[i].posi.y);
		printf("cur_z %.3f, height %.3f, width %.3f, \n", game->sprites[i].cur_z, game->sprites[i].height, game->sprites[i].width);
		i++;
	}
}



void	setup_common_spritecast(t_game *game, t_sp_cast *cast)
{
	cast->win_w = game->win.width;
	cast->win_h = game->win.height;
	cast->play_posi = game->player.map_posi;
	cast->play_dir = vec2d_multi(game->player.dir_vec, game->player.cur_dir_len);
	cast->play_plane = game->player.plane;
	cast->pitch_mod = game->player.pitch;
	cast->play_z_mod = game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod;
	cast->inv_camera = 1.0f / (cast->play_plane.x * cast->play_dir.y - cast->play_plane.y * cast->play_dir.x);

}


void	setup_this_spritecast(t_game *game, t_sp_cast *cast, int i)
{
	cast->sprite = game->sorted[i];
	cast->tex = &game->tex[cast->sprite->tex];
	cast->relative = vec2d_sub(cast->sprite->posi, cast->play_posi);
	cast->trans.x = (cast->play_dir.y * cast->relative.x - cast->play_dir.x * cast->relative.y);
	cast->trans.y = (-cast->play_plane.y * cast->relative.x + cast->play_plane.x * cast->relative.y);
	cast->trans = vec2d_multi(cast->trans, cast->inv_camera);
	cast->sp_z_mod = (0.5f - cast->sprite->height / 2 - cast->sprite->cur_z + cast->sprite->height / 2 * (cast->sprite->type == BULLET));
	cast->centre_pix_x = (int)((cast->win_w / 2) * (1 + cast->trans.x / cast->trans.y));
	cast->sp_pix_h = ft_abs((int)(cast->win_h * cast->sprite->height / cast->trans.y));
	cast->sp_pix_w = ft_abs((int)(cast->win_w * cast->sprite->unit_size * 2 / cast->trans.y));
	cast->total_z_mod = cast->win_h / 2 + cast->pitch_mod \
		- (int)(((cast->play_z_mod + cast->sp_z_mod) * cast->win_h \
		- cast->win_h / 2) / cast->trans.y);
	cast->bot_pix_y = cast->total_z_mod - cast->sp_pix_h / 2;
	cast->top_pix_y = cast->total_z_mod + cast->sp_pix_h / 2;
	cast->left_pix_x = cast->centre_pix_x - cast->sp_pix_w / 2;
	cast->right_pix_x = cast->centre_pix_x + cast->sp_pix_w / 2;
	cast->tex_step_x = cast->tex->height / (float)cast->sp_pix_w;
	cast->tex_step_y = cast->tex->width / (float)cast->sp_pix_h;
	cast->tex_exact_x = 0;
	cast->tex_exact_y = 0;
	cast->shade_wgt = cast->trans.y / (game->max_vis_dist / game->player.cur_dir_len * game->player.base_dir_len);
}


void	sprite_cast(t_game *game)
{
	t_sp_cast	cast;
	int			i;
	int			x;
	int			y;

	setup_common_spritecast(game, &cast);
	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sorted[i]->type == DOOR)
			doorcast(game, game->sorted[i]);
		else if (game->sorted[i]->status != GONE)
		{
			setup_this_spritecast(game, &cast, i);

			if (cast.trans.y > 0)
			{
				cast.tex_exact_x = cast.tex_step_x * (0 - cast.left_pix_x) * (0 > cast.left_pix_x);
				x = ft_max(0, cast.left_pix_x);
				cast.right_pix_x = ft_min(cast.win_w - 1, cast.right_pix_x);
				while (x < cast.right_pix_x)
				{
					cast.tex_pix_x = (int)(cast.tex_exact_x);
					cast.tex_exact_x += cast.tex_step_x;
					if (cast.sprite->inverted)
						cast.tex_pix_x = cast.tex->height - cast.tex_pix_x - 1;
					if (x > 0 && x < cast.win_w && cast.trans.y < game->hori_rays[x].wall_dist)
					{
						cast.tex_exact_y = cast.tex_step_y * (0 - cast.bot_pix_y) * (0 > cast.bot_pix_y);
						y = ft_max(0, cast.bot_pix_y);
						cast.top_pix_y = ft_min(cast.win_h - 1, cast.top_pix_y);
						while (y < cast.top_pix_y)
						{
							cast.tex_pix_y = (int)(cast.tex_exact_y);
							cast.tex_exact_y += cast.tex_step_y;
							cast.color = tex_get_pixel(&game->win, cast.tex, cast.tex_pix_x * cast.tex->width + cast.tex_pix_y);
							if (cast.color != 0)
							{
								cast.color = add_shade(cast.color, cast.shade_wgt);
								game->win.set_pixel(&game->win, x, y, cast.color);
							}

							//printf("placing %d, %d\n", x, y);

							y++;
						}
					}
					x++;
				}
			}



		}
		i++;
	}
}
