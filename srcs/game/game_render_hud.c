/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game-render_hud.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 15:07:54 by marvin            #+#    #+#             */
/*   Updated: 2024/02/16 15:07:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

void	render_gun(t_game *game)
{
	t_xpm_to_win	xpm;

	xpm = (t_xpm_to_win){};
	xpm.tex = &game->tex[GUN_TEX];
	xpm.win_low_x = 300;
	xpm.win_low_y = 0;
	xpm.pix_width = 300;
	xpm.pix_height = 200;
	xpm_to_window(&game->win, &xpm);
}

void	render_stats_bars(t_game *game)
{
	t_hud_stats	*stats;

	stats = &game->stats;

	int statsss[CTR_SIZE];

	int separator;
	int y;
	render_gun(game);
	if(!((game->win.keys >> BIT_HUD_T) & 1))
		return ;
	ft_memcpy(statsss, game->player.health, sizeof(*statsss) * CTR_SIZE);
	separator = ((float)(statsss[CTR_CUR] - statsss[CTR_MIN]) / (float)(statsss[CTR_MAX] - statsss[CTR_MIN]) * (stats->health_end.x - stats->health_start.x)) + stats->health_start.x;

	y = stats->health_start.y;
	while (y < stats->health_end.y)
	{
		bersenham_line(&game->win, (t_pixel){stats->health_start.x, y, 0}, (t_pixel){separator, y, 0}, stats->health_color);
		if (separator + 1 < stats->health_end.x)
			bersenham_line(&game->win, (t_pixel){separator + 1, y, 0}, (t_pixel){stats->health_end.x, y, 0}, stats->empty_color);
		y++;
	}

	ft_memcpy(statsss, game->player.ammo, sizeof(*statsss) * CTR_SIZE);
	separator = ((float)(statsss[CTR_CUR] - statsss[CTR_MIN]) / (float)(statsss[CTR_MAX] - statsss[CTR_MIN]) * (stats->ammo_end.x - stats->ammo_start.x)) + stats->ammo_start.x;

	y = stats->ammo_start.y;
	while (y < stats->ammo_end.y)
	{
		bersenham_line(&game->win, (t_pixel){stats->ammo_start.x, y, 0}, (t_pixel){separator, y, 0}, stats->ammo_color);
		if (separator + 1 < stats->ammo_end.x)
			bersenham_line(&game->win, (t_pixel){separator + 1, y, 0}, (t_pixel){stats->ammo_end.x, y, 0}, stats->empty_color);
		y++;
	}
}
