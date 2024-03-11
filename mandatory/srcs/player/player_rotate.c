/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 14:44:15 by marvin            #+#    #+#             */
/*   Updated: 2024/02/02 14:44:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	player_rotate_and_pitch(t_game *game)
{
	float	rotate;

	rotate = game->player.rot_sense * (((game->win.keys >> BIT_ROT_L) & 1) \
		- ((game->win.keys >> BIT_ROT_R) & 1));
	game_rotate_view_angle(game, rotate);
}
