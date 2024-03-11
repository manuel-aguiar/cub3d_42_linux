/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floorcast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 15:51:01 by marvin            #+#    #+#             */
/*   Updated: 2024/02/07 15:51:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	floorcast_rgb(t_game *game)
{
	t_verti_line	line;

	line.color = game->map.tex_data[F_TEX].color;
	line.x = 0;
	while (line.x < game->win.width)
	{
		line.min_y = 0;
		line.max_y = int_clamp(game->hori_rays[line.x].min_y - 1, \
			0, game->win.height - 1);
		if (line.min_y != line.max_y)
			draw_vertical_line(&game->win, &line);
		line.x++;
	}
}
