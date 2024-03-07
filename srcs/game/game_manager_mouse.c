/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_manager_mouse.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 13:52:57 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 13:52:57 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	game_mouse_manager(t_game *game)
{
	game->player.is_aiming = ((game->win.mouse.buttons >> BIT_AIM) & 1);
	game->player.cur_shot_time \
		= ft_max(game->player.cur_shot_time - game->clock.elapsed, 0);
	if (((game->win.mouse.buttons >> BIT_SHOOT) & 1) \
	&& game->player.cur_shot_time == 0 \
	&& game->player.ammo[CTR_CUR] > 0)
	{
		start_friendly_bullet(game);
		game->player.ammo[CTR_CUR]--;
		game->player.cur_shot_sense = game->player.shot_init;
		game->player.cur_shot_time = game->player.min_shot_time;
	}
}
