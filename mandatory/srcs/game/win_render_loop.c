/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_render_loop.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:21:38 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 10:21:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	rendering_loop(t_game *game)
{
	mlx_hook(game->win.mlx_win, 2, (1L << 0), key_press, &game->win);
	mlx_hook(game->win.mlx_win, 3, (1L << 1), key_release, &game->win);
	mlx_hook(game->win.mlx_win, 17, (1L << 1), free_game, game);
	mlx_do_key_autorepeatoff(game->win.mlx);
	mlx_loop_hook(game->win.mlx, game_render, game);
	mlx_loop(game->win.mlx);
	return (1);
}
