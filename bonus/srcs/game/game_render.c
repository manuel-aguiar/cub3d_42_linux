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

static inline void	game_is_lost(t_game *game)
{
	if (game->cur_time_lost_str >= game->total_time_lost_str)
		free_game(game);
	else
	{
		game->cur_time_lost_str += (game->clock.elapsed + 1);
		window_pause_manager(&game->win, PAUSE_ON, \
			game->blur_is_on);
		game->win.string = you_lost_text_string;
	}
}

static void	render_as_usual(t_game *game)
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

static inline void	apply_game_state(t_game *game)
{
	if (game->is_lost)
		game_is_lost(game);
	else if ((game->win.keys >> BIT_PAUSE_T) & 0xff)
	{
		window_pause_manager(&game->win, PAUSE_ON, \
			game->blur_is_on);
		game->win.string = pause_text_string;
	}
	else if (game->win.blur.elapsed > 0)
	{
		window_pause_manager(&game->win, PAUSE_OFF, \
			game->blur_is_on);
		game->win.string = pause_text_string;
	}
	else
		render_as_usual(game);
}

int	game_render(t_game *game)
{
	game->win.string = NULL;
	game_actions(game);
	game->blur_is_on = (game->win.keys >> BIT_BLUR_T) & 1;
	apply_game_state(game);
	mlx_put_image_to_window(game->win.mlx, game->win.mlx_win, \
		game->win.front_buf.img, 0, 0);
	if (game->enemy_count == 0 && game->cur_time_win_str < \
		game->total_time_win_str)
	{
		game->cur_time_win_str += game->clock.elapsed;
		game->win.string = enemies_defeated_text_string;
	}
	if (game->win.string)
		game->win.string(&game->win);
	return (1);
}
