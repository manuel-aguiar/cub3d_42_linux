/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ceilcast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:09:47 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 21:54:08 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	ceiling_rgb(t_game *game)
{
	t_verti_line	line;

	line.color = game->map.tex_data[C_TEX].color;
	line.x = 0;
	line.max_y = game->win.height - 1;
	while (line.x < game->win.width)
	{
		line.min_y = int_clamp(game->hori_rays[line.x].max_y + 1, \
			0, game->win.height - 1);
		if (line.min_y != line.max_y)
			draw_vertical_line(&game->win, &line);
		line.x++;
	}
}
