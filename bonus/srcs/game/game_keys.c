/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_keys.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 12:23:14 by marvin            #+#    #+#             */
/*   Updated: 2024/01/30 12:23:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	game_setup_keys(t_game *game)
{
	game->win.keys |= (1 << BIT_HUD_T);
	game->win.keys |= (1 << BIT_BLUR_T);
	game->win.keys |= (1 << BIT_SHADE_T);
	game->win.keys |= (1 << BIT_FLOOR_REFL_T);
	game->win.keys |= (1 << BIT_CEIL_REFL_T);
}
