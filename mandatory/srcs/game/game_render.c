/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 12:37:43 by marvin            #+#    #+#             */
/*   Updated: 2024/01/23 12:37:43 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	render_as_usual(t_game *game)
{
	ft_memset(game->win.front_buf.pixels, 0, \
		game->win.width * game->win.height * game->win.rgb_size);
	hori_raycasting(game);
	floorcast_rgb(game);
	ceiling_rgb(game);
}

int	game_render(t_game *game)
{
	game_actions(game);
	render_as_usual(game);
	mlx_put_image_to_window(game->win.mlx, game->win.mlx_win, \
		game->win.front_buf.img, 0, 0);
	return (1);
}
