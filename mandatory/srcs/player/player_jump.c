/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_jump.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 15:57:01 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 15:57:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

/*
https://jsfiddle.net/LyM87/
*/

void	player_jump_gravity(t_player *player)
{
	if (player->hgt_state == HGT_JUMP)
	{
		player->jump_z_mod += player->cur_jump_sense \
			* player->clock->elapsed;
		player->cur_jump_sense -= player->vertical_gravity \
			* player->clock->elapsed;
		if (player->jump_z_mod < 0)
		{
			player->jump_z_mod = 0;
			player->hgt_state = HGT_NORMAL;
		}
	}
	else
		player->cur_jump_sense = 0;
}
