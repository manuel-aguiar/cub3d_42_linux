/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_key_manager.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:43:50 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 12:43:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	game_key_manager(t_game *game)
{
	int	keys;
	int	move;
	int	new_height_state;

	keys = game->win.keys;
	move = (((keys >> BIT_FRONT) & 1) << 3) \
		| (((keys >> BIT_BACK) & 1) << 2) \
		| (((keys >> BIT_LEFT) & 1) << 1) \
		| (((keys >> BIT_RIGHT) & 1));
	move_player(game, move);
	new_height_state = -1;
	game->player.hgt_manager[game->player.hgt_state](&game->player, \
		&game->win.keys, &new_height_state);
	if (new_height_state != -1)
		game->player.hgt_state = new_height_state;
	game->win.keys &= ~(1 << BIT_CROUCH);
	game->win.keys &= ~(1 << BIT_PRONE);
	game->player.is_sprinting = ((keys >> BIT_SPRINT) & 1) \
		&& !game->player.is_aiming && (((keys >> BIT_FRONT) & 1));
}
