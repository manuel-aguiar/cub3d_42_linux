/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_crouch.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 20:13:44 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 20:13:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

void	player_change_stance(t_player *player)
{
	float	target;
	int		up_down;

	target = player->stance_z[HGT_NORMAL];
	if (player->hgt_state == HGT_PRONE)
		target = player->stance_z[HGT_PRONE];
	if (player->hgt_state == HGT_CROUCH)
		target = player->stance_z[HGT_CROUCH];
	if (player->cur_z >= target)
		up_down = -1;
	else
		up_down = 1;
	player->cur_z += up_down * player->hgt_sense * player->clock->elapsed;
	if ((up_down == -1 && player->cur_z <= target) \
	|| (up_down == 1 && player->cur_z >= target))
		player->cur_z = target;
}
