/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_player.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:08:30 by marvin            #+#    #+#             */
/*   Updated: 2024/02/29 13:08:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_settings.h"

static inline void	settings_player_two(t_player *player)
{
	player->cur_move_multi = PLAY_NORMAL_MOVE_MULTI;
	player->move_multi[HGT_NORMAL] = PLAY_NORMAL_MOVE_MULTI;
	player->move_multi[HGT_CROUCH] = PLAY_CROUCH_MOVE_MULTI;
	player->move_multi[HGT_PRONE] = PLAY_PRONE_MOVE_MULTI;
	player->move_multi[HGT_JUMP] = 1.0f;
	player->aim_move_multi = PLAY_AIM_MOVE_MULTI;
	player->sprint_move_multi = PLAY_SPRINT_MOVE_MULTI;
}

void	settings_player(t_player *player)
{
	player->forward_move = PLAY_FORWARD_MOVE_SENSE;
	player->side_move = PLAY_SIDE_MOVE_SENSE;
	player->back_move = PLAY_BACK_MOVE_SENSE;
	player->rot_sense = PLAY_ROT_SENSE;
	player->unit_size = PLAY_UNIT_SIZE;
	player->pitch = PLAY_BASE_PITCH;
	player->hgt_state = HGT_NORMAL;
	player->cur_z = PLAY_HGT_NORMAL;
	player->base_fov = PLAY_BASE_FOV;
	player->cur_fov = player->base_fov;
	player->base_dir_len = PLAY_BASE_DIR_LEN;
	player->aim_dir_len = PLAY_AIM_DIR_LEN;
	player->cur_dir_len = player->base_dir_len;
	player->aim_sense = PLAY_AIM_SENSE;
	settings_player_two(player);
}
