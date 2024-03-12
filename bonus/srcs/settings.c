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

static void	settings_hud(t_hud_stats *hud)
{
	hud->health_color = rgba(125, 0, 0, 255);
	hud->ammo_color = rgba(0, 0, 125, 255);
	hud->empty_color = rgba(25, 25, 25, 255);
	hud->health_start = (t_pixel){550, 60, 0};
	hud->health_end = (t_pixel){750, 85, 0};
	hud->ammo_start = (t_pixel){550, 25, 0};
	hud->ammo_end = (t_pixel){750, 50, 0};
}

static inline void	settings_compass_two(t_game *game, t_compass *comp)
{
	comp->map_centre = (t_pixel){WIN_WIDTH / 2, WIN_HEIGHT / 4, \
		rgba(255, 255, 255, 255)};
	comp->sqr.height = game->compass.sqr_height;
	comp->sqr.centre = (t_pixel){0, 0, game->compass.sqr_color};
	comp->sqr.color = game->compass.sqr_color;
	comp->sqr.biggest_z = 1 + sqrt((COMP_MAX_RAD * SQR_MAX_HEIGHT_PERC) \
		* (COMP_MAX_RAD * SQR_MAX_HEIGHT_PERC) * 2);
	comp->player_rad = game->compass.sqr.height * COMP_PLAY_RAD;
	comp->player_colour = rgba(0, 0, 255, 255);
	comp->blur_on = BLUR_ON;
	comp->blur = (t_comp_blur){};
	comp->blur.max_kernel = BLUR_KERNEL_MAX;
	comp->blur.kernel_size = BLUR_KERNEL_SIZE;
	comp->blur.sigma = BLUR_KERNEL_SIGMA;
}

void	settings_compass(t_game *game, t_compass *comp)
{
	comp->centre = (t_pixel){game->win.width / 6, game->win.height / 4, \
		rgba(255, 0, 0, 0)};
	comp->radius = int_clamp(game->win.height / 5, COMP_MIN_RAD, COMP_MAX_RAD);
	comp->color = rgba(50, 0, 0, 255);
	comp->inner.radius = game->compass.radius * COMP_INNER_RAD_PERC;
	comp->inner.color = rgba(50, 0, 0, 255);
	comp->letter_radius = game->compass.radius * COMP_LETTER_RAD_PERC;
	comp->letter_width = game->compass.radius * COMP_LETTER_WDT_PERC;
	comp->letter_height = game->compass.radius * COMP_LETTER_HGT_PERC;
	comp->letter_color = rgba(255, 255, 255, 255);
	comp->sqr_color = rgba(50, 25, 0, 255);
	comp->sqr_height = int_clamp (\
					(int)(game->compass.radius * SQR_HEIGHT_PERC), \
					(int)(game->compass.radius * SQR_MIN_HEIGHT_PERC), \
					(int)(game->compass.radius * SQR_MAX_HEIGHT_PERC));
	settings_compass_two(game, comp);
	settings_hud(&game->stats);
}

void	settings_window(t_win *win)
{
	win->width = int_clamp(WIN_WIDTH, MIN_WIN_WIDTH, MAX_WIN_WIDTH);
	win->height = int_clamp(WIN_HEIGHT, MIN_WIN_HEIGHT, MAX_WIN_HEIGHT);
	win->rgb_size = RGB_SIZE;
	ft_memcpy(win->name, WIN_NAME, sizeof(win->name));
	win->blur = (t_pause_blur){};
	win->blur.max_kernel = BLUR_KERNEL_MAX;
	win->blur.kernel_size = BLUR_KERNEL_SIZE;
	win->blur.kernel_centre = win->blur.kernel_size / 2;
	win->blur.cur_sigma = WIN_MIN_SIGMA;
	win->blur.min_sigma = WIN_MIN_SIGMA;
	win->blur.max_sigma = WIN_MAX_SIGMA;
	win->blur.pause_time = WIN_PAUSE_TIME;
	win->blur.elapsed = 0;
	win->blur.rgb_size = win->rgb_size;
	win->blur.height = win->height;
	win->blur.width = win->width;
}

void	apply_all_settings(t_game *game)
{
	settings_window(&game->win);
	settings_player(&game->player);
	settings_compass(game, &game->compass);
	settings_all_templates(game);
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
