/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:44:15 by marvin            #+#    #+#             */
/*   Updated: 2024/02/02 14:44:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static inline void	player_shot_pitch(t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (player->cur_shot_sense != 0)
	{
		if (player->shot_pitch_mod > 1.0f)
			player->cur_shot_sense /= player->shot_pitch_mod;
		player->shot_pitch_mod += player->cur_shot_sense \
			* player->clock->elapsed;
		player->cur_shot_sense -= player->shot_gravity \
			* player->clock->elapsed;
	}
	if (player->shot_pitch_mod <= 0)
	{
		player->shot_pitch_mod = 0;
		player->cur_shot_sense = 0;
	}
}

static inline void	update_player_3d_coords(t_game *game)
{
	game->player.posi_3d = (t_vec3d){game->player.map_posi.x, \
		game->player.map_posi.y, \
		(game->player.cur_z + game->player.jump_z_mod + \
		game->player.walk_z_mod)};
	game->player.dir_3d = (t_vec3d){game->player.cos_rad, \
		game->player.sin_rad, -game->player.verti_tan \
		* game->player.vertical_correction};
}

void	player_rotate_and_pitch(t_game *game)
{
	float	rotate;
	float	rotate_aim_multi;
	float	pitch;

	rotate_aim_multi = 1;
	if (game->player.is_aiming)
		rotate_aim_multi = game->player.aim_rot_multi;
	rotate = (game->win.width / 2 - game->win.mouse.cur_x) \
		* game->player.rot_sense * rotate_aim_multi \
		* game->player.clock->elapsed;
	game_rotate_view_angle(game, rotate);
	pitch = ((game->win.mouse.cur_y - game->win.height / 2) \
		* game->player.pitch_sense * rotate_aim_multi \
		* game->player.clock->elapsed);
	player_shot_pitch(game);
	game->player.verti_angle = float_clamp(game->player.verti_angle \
		+ pitch, game->player.verti_min, game->player.verti_max);
	game->player.verti_tan = tanf(float_clamp(game->player.verti_angle \
		- game->player.shot_pitch_mod, game->player.verti_min, \
		game->player.verti_max));
	game->player.pitch = (int)(game->player.cur_dir_len / \
		game->player.base_dir_len * game->player.verti_tan \
		* game->win.height / 2);
	update_player_3d_coords(game);
}
