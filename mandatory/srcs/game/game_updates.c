/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_updates.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 09:55:22 by codespace         #+#    #+#             */
/*   Updated: 2024/03/11 21:46:41 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	game_actions(t_game *game)
{
	if ((game->win.keys >> BIT_ESC) & 1)
		free_game(game);
	game_key_manager(game);
	game_mouse_manager(game);
	player_actions(game);
}
