/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:23:32 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 19:23:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	player_setup(t_player *player)
{
	player->is_aiming = false;
	player->is_sprinting = false;
	player->is_walking = false;
	player->plane = vec2d_multi((t_vec2d){player->sin_rad, \
		-player->cos_rad}, player->cur_fov);
	player->move[0] = move_player_default;
	player->move[1] = move_player_right;
	player->move[2] = move_player_left;
	player->move[3] = move_player_default;
	player->move[4] = move_player_backward;
	player->move[5] = move_player_back_right;
	player->move[6] = move_player_back_left;
	player->move[7] = move_player_backward;
	player->move[8] = move_player_forward;
	player->move[9] = move_player_for_right;
	player->move[10] = move_player_for_left;
	player->move[11] = move_player_forward;
	player->move[12] = move_player_default;
	player->move[13] = move_player_right;
	player->move[14] = move_player_left;
	player->move[15] = move_player_default;
	player->hgt_manager[HGT_PRONE] = manage_prone_height;
	player->hgt_manager[HGT_CROUCH] = manage_crouch_height;
	player->hgt_manager[HGT_NORMAL] = manage_normal_height;
	player->hgt_manager[HGT_JUMP] = manage_jump_height;
}

void	player_actions(t_game *game)
{
	t_player	*player;

	player = &game->player;
	player_change_aim(player);
	player_change_stance(player);
	player_jump_gravity(player);
	player_walk_height(player, game);
	player_rotate_and_pitch(game);
}
