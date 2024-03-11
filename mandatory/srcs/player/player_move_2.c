/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 13:29:37 by marvin            #+#    #+#             */
/*   Updated: 2024/02/29 13:29:37 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_vec2d	move_player_default(t_player *player)
{
	(void)player;
	return ((t_vec2d){0, 0});
}

t_vec2d	move_player_back_left(t_player *player)
{
	t_vec2d	diagonal;
	float	speed;

	speed = player->back_move * player->cur_move_multi \
		* 1;
	diagonal.x = 1 * (P_SQRT_OF_TWO_OVER_TWO \
		* player->cos_rad - P_SQRT_OF_TWO_OVER_TWO * player->sin_rad);
	diagonal.y = -1 * (P_SQRT_OF_TWO_OVER_TWO \
		* player->sin_rad + P_SQRT_OF_TWO_OVER_TWO * player->cos_rad);
	return (vec2d_multi(vec2d_swap_coords(diagonal), speed));
}

t_vec2d	move_player_back_right(t_player *player)
{
	t_vec2d	diagonal;
	float	speed;

	speed = player->back_move * player->cur_move_multi \
		* 1;
	diagonal.x = -1 * (P_SQRT_OF_TWO_OVER_TWO \
		* player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad);
	diagonal.y = 1 * (P_SQRT_OF_TWO_OVER_TWO \
		* player->sin_rad - P_SQRT_OF_TWO_OVER_TWO * player->cos_rad);
	return (vec2d_multi(vec2d_swap_coords(diagonal), speed));
}

t_vec2d	move_player_for_left(t_player *player)
{
	t_vec2d	diagonal;
	float	speed;

	speed = player->side_move * player->cur_move_multi \
		* 1;
	if (player->is_sprinting \
	&& (player->hgt_state == HGT_NORMAL || player->hgt_state == HGT_JUMP))
		speed *= player->sprint_move_multi;
	diagonal.x = 1 * (P_SQRT_OF_TWO_OVER_TWO \
		* player->cos_rad + P_SQRT_OF_TWO_OVER_TWO * player->sin_rad);
	diagonal.y = -1 * (P_SQRT_OF_TWO_OVER_TWO \
		* player->sin_rad - P_SQRT_OF_TWO_OVER_TWO * player->cos_rad);
	return (vec2d_multi(vec2d_swap_coords(diagonal), speed));
}

t_vec2d	move_player_for_right(t_player *player)
{
	t_vec2d	diagonal;
	float	speed;

	speed = player->side_move * player->cur_move_multi \
		* 1;
	if (player->is_sprinting \
	&& (player->hgt_state == HGT_NORMAL || player->hgt_state == HGT_JUMP))
		speed *= player->sprint_move_multi;
	diagonal.x = -1 * (P_SQRT_OF_TWO_OVER_TWO \
		* player->cos_rad - P_SQRT_OF_TWO_OVER_TWO * player->sin_rad);
	diagonal.y = 1 * (P_SQRT_OF_TWO_OVER_TWO \
		* player->sin_rad + P_SQRT_OF_TWO_OVER_TWO * player->cos_rad);
	return (vec2d_multi(vec2d_swap_coords(diagonal), speed));
}
