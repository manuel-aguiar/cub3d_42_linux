/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 19:30:57 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 19:30:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

t_vec2d	move_player_left(t_player *player)
{
	float	speed;

	speed = player->side_move * player->cur_move_multi \
		* 1;
	return (vec2d_multi((t_vec2d){-player->dir_vec.y, \
		+ player->dir_vec.x}, speed));
}

t_vec2d	move_player_right(t_player *player)
{
	float	speed;

	speed = player->side_move * player->cur_move_multi \
		* 1;
	return (vec2d_multi((t_vec2d){+player->dir_vec.y, \
		- player->dir_vec.x}, speed));
}

t_vec2d	move_player_backward(t_player *player)
{
	return (vec2d_multi(vec2d_multi(player->dir_vec, player->back_move \
		* player->cur_move_multi * 1), -1));
}

t_vec2d	move_player_forward(t_player *player)
{
	float	speed;

	speed = player->forward_move * player->cur_move_multi;
	if (player->is_sprinting \
	&& (player->hgt_state == HGT_NORMAL || player->hgt_state == HGT_JUMP))
		speed *= player->sprint_move_multi;
	return (vec2d_multi(player->dir_vec, speed \
		* 1));
}

void	move_player(t_game *game, int keys)
{
	t_player	*player;
	t_vec2d		potential;

	player = &game->player;
	player->cur_move_multi = player->move_multi[player->hgt_state];
	if (!keys || keys == 3 || keys == 12 || keys == 15)
		return ;
	potential = player->move[keys](player);
	handle_collisions(game, &player->map_posi, potential, player->unit_size);
}
