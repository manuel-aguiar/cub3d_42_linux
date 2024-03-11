/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:45:51 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:45:51 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_settings.h"

void	settings_window(t_win *win)
{
	win->width = int_clamp(WIN_WIDTH, MIN_WIN_WIDTH, MAX_WIN_WIDTH);
	win->height = int_clamp(WIN_HEIGHT, MIN_WIN_HEIGHT, MAX_WIN_HEIGHT);
	win->rgb_size = RGB_SIZE;
	ft_memcpy(win->name, WIN_NAME, sizeof(win->name));
}

void	apply_all_settings(t_game *game)
{
	settings_window(&game->win);
	settings_player(&game->player);
	game->max_vis_dist = MAX_VISIBLE_DISTANCE;
	game->wall_reflection = GAME_WALL_REFLECTION;
	game->float_sense = GAME_FLOAT_SENSE;
	game->max_bullets = 0;
	game->max_bullets = MAX_BULLETS;
	game->live_bullets = 0;
	game->cur_time_win_str = 0;
	game->total_time_win_str = GAME_WIN_TIME;
	game->is_lost = false;
	game->cur_time_lost_str = 0;
	game->total_time_lost_str = GAME_LOST_TIME;
	game->exit_status = EXIT_SUCCESS;
}
