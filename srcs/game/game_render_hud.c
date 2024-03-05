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
	xpm_to_window(&game->win, &game->tex[GUN_TEX], (t_pixel){300, 0, 0}, 300, 200);
}


void	render_stats_bars(t_game *game)
{
	t_pixel health_start;
	t_pixel	health_end;

	t_pixel ammo_start;
	t_pixel	ammo_end;
	int stats[CTR_SIZE];

	int health_color = rgba(125,0,0,255);
	int	ammo_color = rgba(0,0,125,255);
	int empty_color = rgba(25,25,25,255);

	int separator;
	int y;
	render_gun(game);
	if(!(game->win.keys >> BIT_HUD_T) & 1)
		return ;
	health_start = (t_pixel){550, 60, 0};
	health_end = (t_pixel){750, 85, 0};

	ammo_start = (t_pixel){550, 25, 0};
	ammo_end = (t_pixel){750, 50, 0};

	ft_memcpy(stats, game->player.health, sizeof(*stats) * CTR_SIZE);
	separator = ((float)(stats[CTR_CUR] - stats[CTR_MIN]) / (float)(stats[CTR_MAX] - stats[CTR_MIN]) * (health_end.x - health_start.x)) + health_start.x;

	y = health_start.y;
	while (y < health_end.y)
	{
		bersenham_line(&game->win, (t_pixel){health_start.x, y, 0}, (t_pixel){separator, y, 0}, health_color);
		if (separator + 1 < health_end.x)
			bersenham_line(&game->win, (t_pixel){separator + 1, y, 0}, (t_pixel){health_end.x, y, 0}, empty_color);
		y++;
	}

	ft_memcpy(stats, game->player.ammo, sizeof(*stats) * CTR_SIZE);
	separator = ((float)(stats[CTR_CUR] - stats[CTR_MIN]) / (float)(stats[CTR_MAX] - stats[CTR_MIN]) * (ammo_end.x - ammo_start.x)) + ammo_start.x;

	y = ammo_start.y;
	while (y < ammo_end.y)
	{
		bersenham_line(&game->win, (t_pixel){ammo_start.x, y, 0}, (t_pixel){separator, y, 0}, ammo_color);
		if (separator + 1 < ammo_end.x)
			bersenham_line(&game->win, (t_pixel){separator + 1, y, 0}, (t_pixel){ammo_end.x, y, 0}, empty_color);
		y++;
	}
}
