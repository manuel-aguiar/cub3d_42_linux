/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_walk_height.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:25:40 by marvin            #+#    #+#             */
/*   Updated: 2024/02/02 14:25:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static inline void	player_isnt_walking(t_player *player)
{
	if (player->walk_z_mod > 0)
		player->walk_z_mod = float_clamp(player->walk_z_mod \
		- 0.0005f * player->clock->elapsed, 0, player->walk_z_mod);
	else if (player->walk_z_mod < 0)
		player->walk_z_mod = float_clamp(player->walk_z_mod \
		+ 0.0005f * player->clock->elapsed, player->walk_z_mod, 0);
	player->cur_walk_sense = 0;
}

void	player_walk_height(t_player *player, t_game *game)
{
	float	speed;
	float	radius;

	if ((player->is_walking && player->hgt_state != HGT_JUMP))
	{
		speed = player->cur_move_multi;
		if (player->is_sprinting && player->hgt_state == HGT_NORMAL \
		&& (game->win.keys >> BIT_FRONT) & 1)
			speed *= player->sprint_move_multi;
		player->cur_walk_sense += 0.015f * speed * player->clock->elapsed;
		radius = player->walk_radius;
		if (player->hgt_state == HGT_CROUCH)
			radius = player->crouch_radius;
		if (player->hgt_state == HGT_PRONE)
			radius = player->prone_radius;
		player->walk_z_mod = -sinf(player->cur_walk_sense) \
			/ (speed) * radius * float_ternary(player->is_aiming, 0.25f, 1);
		if (player->cur_walk_sense > 2 * MY_PI)
		{
			player->is_walking = false;
			player->walk_z_mod = 0;
		}
	}
	else
		player_isnt_walking(player);
}
