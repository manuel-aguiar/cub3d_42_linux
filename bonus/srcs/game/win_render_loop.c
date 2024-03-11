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
	mlx_hook(game->win.mlx_win, 4, (1L << 2), mouse_press, &game->win);
	mlx_hook(game->win.mlx_win, 5, (1L << 3), mouse_release, &game->win);
	mlx_hook(game->win.mlx_win, 6, (1L << 6), mouse_position, &game->win);
	mlx_hook(game->win.mlx_win, 17, (1L << 1), free_game, game);
	mlx_do_key_autorepeatoff(game->win.mlx);
	mlx_mouse_move(game->win.mlx, game->win.mlx_win, \
		game->win.width / 2, game->win.height / 2);
	update_clock(&game->clock);
	mlx_loop_hook(game->win.mlx, game_render, game);
	mlx_loop(game->win.mlx);
	return (1);
}
