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

int	game_is_paused(t_game *game)
{
	if ((game->win.keys >> BIT_PAUSE_T) & 1 \
		|| (!((game->win.keys >> BIT_PAUSE_T) & 1) \
		&& game->win.blur.elapsed > 0) \
		|| game->is_lost)
		return (1);
	return (0);
}

void	game_is_lost(t_game *game)
{
	if (game->cur_time_lost_str >= game->total_time_lost_str)
		free_game(game);
	else
	{
		game->cur_time_lost_str += game->clock.elapsed;
		window_pause_manager(&game->win, PAUSE_ON, \
			game->blur_is_on, you_lost_text_string);
	}
}

void	render_as_usual(t_game *game)
{
	ft_memset(game->win.front_buf.pixels, 0, \
		game->win.width * game->win.height * game->win.rgb_size);
	hori_raycasting(game);
	floorcast(game);
	ceilcast(game);
	sprite_cast(game);
	game->compass.blur_on = game->blur_is_on;
	if (((game->win.keys) >> BIT_HUD_T) & 1)
	{
		render_compass(&game->win, &game->compass);
		render_map_inside_compass(game);
		render_player_inside_compass(game);
		render_stats_bars(game);
	}
}

int	game_render(t_game *game)
{
	game_actions(game);
	game->blur_is_on = (game->win.keys >> BIT_BLUR_T) & 1;
	if ((game->win.keys >> BIT_PAUSE_T) & 0xff)
		window_pause_manager(&game->win, PAUSE_ON, \
			game->blur_is_on, pause_text_string);
	else if (game->win.blur.elapsed > 0)
		window_pause_manager(&game->win, PAUSE_OFF, \
			game->blur_is_on, pause_text_string);
	else if (game->is_lost)
		game_is_lost(game);
	else
		render_as_ususal(game);
	game->win.set_pixel(&game->win, game->win.width / 2, \
		game->win.height / 2, (unsigned int)-1);
	if (game->enemy_count == 0 && game->cur_time_win_str < \
		game->total_time_win_str)
	{
		game->cur_time_win_str += game->clock.elapsed;
		enemies_defeated_text_string(&game->win);
	}
	mlx_put_image_to_window(game->win.mlx, game->win.mlx_win, \
		game->win.front_buf.img, 0, 0);
	return (1);
}
