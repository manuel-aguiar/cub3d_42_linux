/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_aim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 11:51:48 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 11:51:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"

/*
	player aim changes the length of the direction vector
	must also slow movement speed and move rotation sensibilities
	all parameters can be arrays of floats, cur / min / max
*/

void	player_change_aim(t_player *player)
{
	if (player->is_aiming)
	{
		player->cur_dir_len = float_clamp(player->cur_dir_len \
			+ (float)(player->aim_sense * player->clock->elapsed), \
			player->base_dir_len, player->aim_dir_len);
	}
	else
	{
		player->cur_dir_len = float_clamp(player->cur_dir_len \
			- (float)(player->aim_sense * player->clock->elapsed), \
			player->base_dir_len, player->aim_dir_len);
	}
	player->plane = vec2d_multi((t_vec2d){player->sin_rad, -player->cos_rad}, \
		player->cur_fov);
}
