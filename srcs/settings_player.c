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

static inline void	settings_player_three(t_player *player)
{
	player->cur_walk_sense = 0;
	player->walk_z_mod = 0;
	player->walk_sway_mod = 0;
	player->verti_angle = PITCH_ANGLE_BASE;
	player->verti_tan = tanf(player->verti_angle);
	player->verti_min = PITCH_ANGLE_MIN;
	player->verti_max = PITCH_ANGLE_MAX;
	player->health[CTR_CUR] = PLAY_HEALTH_START;
	player->health[CTR_MIN] = PLAY_HEALTH_MIN;
	player->health[CTR_MAX] = PLAY_HEALTH_MAX;
	player->ammo[CTR_CUR] = PLAY_AMMO_START;
	player->ammo[CTR_MIN] = PLAY_AMMO_MIN;
	player->ammo[CTR_MAX] = PLAY_AMMO_MAX;
	player->attack = PLAY_BULLET_DAMAGE;
	player->min_shot_time = PLAY_SHOT_MIN_TIME;
	player->cur_shot_time = 0;
	player->shot_pitch_mod = 0;
	player->shot_init = PLAY_SHOT_INIT;
	player->shot_gravity = PLAY_SHOT_GRAVITY;
	player->cur_shot_sense = 0;
}

static inline void	settings_player_two(t_player *player)
{
	player->aim_rot_multi = PLAY_AIM_ROT_MULTI;
	player->cur_jump_sense = 0;
	player->vertical_gravity = PLAY_VERTICAL_GRAVITY;
	player->jump_init = PLAY_JUMP_INIT;
	player->jump_inc = PLAY_JUMP_INC;
	player->jump_press_cap = PLAY_JUMP_PRESS_CAP;
	player->jump_release_cap = PLAY_JUMP_RELEASE_CAP;
	player->jump_z_mod = 0;
	player->cur_move_multi = PLAY_NORMAL_MOVE_MULTI;
	player->move_multi[HGT_NORMAL] = PLAY_NORMAL_MOVE_MULTI;
	player->move_multi[HGT_CROUCH] = PLAY_CROUCH_MOVE_MULTI;
	player->move_multi[HGT_PRONE] = PLAY_PRONE_MOVE_MULTI;
	player->move_multi[HGT_JUMP] = 1.0f;
	player->aim_move_multi = PLAY_AIM_MOVE_MULTI;
	player->sprint_move_multi = PLAY_SPRINT_MOVE_MULTI;
	player->walking_gravity = PLAY_WALKING_GRAVITY;
	player->walk_radius = PLAY_WALK_RADIUS;
	player->crouch_radius = PLAY_CROUCH_RADIUS;
	player->prone_radius = PLAY_PRONE_RADIUS;
}

void	settings_player(t_player *player)
{
	player->forward_move = PLAY_FORWARD_MOVE_SENSE;
	player->side_move = PLAY_SIDE_MOVE_SENSE;
	player->back_move = PLAY_BACK_MOVE_SENSE;
	player->rot_sense = PLAY_ROT_SENSE;
	player->pitch_sense = PLAY_PITCH_SENSE;
	player->unit_size = PLAY_UNIT_SIZE;
	player->pitch = PLAY_BASE_PITCH;
	player->hgt_state = HGT_NORMAL;
	player->stance_z[HGT_NORMAL] = PLAY_HGT_NORMAL;
	player->stance_z[HGT_PRONE] = PLAY_HGT_PRONE;
	player->stance_z[HGT_CROUCH] = PLAY_HGT_CROUCH;
	player->cur_z = player->stance_z[HGT_NORMAL];
	player->hgt_sense = PLAY_HGT_SENSE;
	player->base_fov = PLAY_BASE_FOV;
	player->cur_fov = player->base_fov;
	player->base_dir_len = PLAY_BASE_DIR_LEN;
	player->aim_dir_len = PLAY_AIM_DIR_LEN;
	player->cur_dir_len = player->base_dir_len;
	player->aim_sense = PLAY_AIM_SENSE;
	settings_player_two(player);
	settings_player_three(player);
}
