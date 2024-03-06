/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_comp_render.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 15:32:06 by marvin            #+#    #+#             */
/*   Updated: 2024/01/25 15:32:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static inline void	render_square_inside_compass(t_game *game, \
					t_pixel centre, int centre_index, int i)
{
	t_pixel	sqr_centre;
	int		sqr_hgt;

	sqr_hgt = game->compass.sqr_height;
	sqr_centre = centre;
	sqr_centre.x += (i % game->map.width - centre_index \
		/ game->map.height) * sqr_hgt;
	sqr_centre.y += (i / game->map.width - centre_index \
		/ game->map.width) * sqr_hgt;
	sqr_centre.x -= (int)((game->player.map_posi.x - centre_index \
		/ game->map.height - 0.5f) * sqr_hgt);
	sqr_centre.y -= (int)((game->player.map_posi.y - centre_index \
		/ game->map.width - 0.5f) * sqr_hgt);
	rotate_point(&sqr_centre, centre, -game->compass.sin_rad, \
		-game->compass.cos_rad);
	render_square_vs_circle(&game->win, &game->compass, sqr_centre);
}

void	render_map_inside_compass(t_game *game)
{
	int		i;
	int		centre_index;
	t_pixel	centre;

	centre = game->compass.centre;
	centre_index = game->map.len / 2;
	i = 0;
	while (i < game->map.len)
	{
		if (game->map.map[i] == MAP_WALL)
			render_square_inside_compass(game, centre, centre_index, i);
		i++;
	}
}

void	render_player_inside_compass(t_game *game)
{
	int			sqr_hgt;
	t_pixel		centre;
	t_player	*player;

	player = &game->player;
	sqr_hgt = game->compass.sqr_height;
	centre = game->compass.centre;
	render_empty_circle_with_aa(&game->win, centre, \
		(int)(player->unit_size * sqr_hgt), game->compass.player_colour);
}
