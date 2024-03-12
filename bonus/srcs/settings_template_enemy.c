/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings_template_enemy.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:45:59 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/12 20:05:57 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_settings.h"

void	settings_template_x_enemy(t_enemy *enemy)
{
	*enemy = (t_enemy){};
	enemy->type = X_ENEMY;
	enemy->unit_size = X_ENEMY_UNIT;
	enemy->height = X_ENEMY_HGT;
	enemy->width = X_ENEMY_WDT;
	enemy->base_z = X_ENEMY_Z;
	enemy->z_sense = X_ENEMY_Z_SENSE;
	enemy->move_sense = X_ENEMY_MOVE_SENSE;
	enemy->ms_to_swap = X_ENEMY_MS_SWAP;
	enemy->elapsed = 0;
	enemy->attack_val = X_ENEMY_ATTACK;
	enemy->health = X_ENEMY_HEALTH;
	enemy->attack_time = X_ENEMY_TIME_ATTACK;
	enemy->attack_elapsed = 0;
}

void	settings_template_y_enemy(t_enemy *enemy)
{
	*enemy = (t_enemy){};
	enemy->type = Y_ENEMY;
	enemy->unit_size = Y_ENEMY_UNIT;
	enemy->height = Y_ENEMY_HGT;
	enemy->width = Y_ENEMY_WDT;
	enemy->base_z = Y_ENEMY_Z;
	enemy->z_sense = Y_ENEMY_Z_SENSE;
	enemy->move_sense = Y_ENEMY_MOVE_SENSE;
	enemy->ms_to_swap = Y_ENEMY_MS_SWAP;
	enemy->elapsed = 0;
	enemy->attack_val = Y_ENEMY_ATTACK;
	enemy->health = Y_ENEMY_HEALTH;
	enemy->attack_time = Y_ENEMY_TIME_ATTACK;
	enemy->attack_elapsed = 0;
}

void	settings_template_z_enemy(t_enemy *enemy)
{
	*enemy = (t_enemy){};
	enemy->type = Z_ENEMY;
	enemy->unit_size = Z_ENEMY_UNIT;
	enemy->height = Z_ENEMY_HGT;
	enemy->width = Z_ENEMY_WDT;
	enemy->base_z = Z_ENEMY_Z;
	enemy->z_sense = Z_ENEMY_Z_SENSE;
	enemy->move_sense = Z_ENEMY_MOVE_SENSE;
	enemy->ms_to_swap = Z_ENEMY_MS_SWAP;
	enemy->elapsed = 0;
	enemy->attack_val = Z_ENEMY_ATTACK;
	enemy->health = Z_ENEMY_HEALTH;
	enemy->attack_time = Z_ENEMY_TIME_ATTACK;
	enemy->attack_elapsed = 0;
	enemy->shot_this_time = 0;
	enemy->shot_max_time = Z_ENEMY_SHOT_MAX_TIME;
	enemy->cur_shot_time = 0;
}
