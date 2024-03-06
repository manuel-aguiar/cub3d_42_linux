/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 19:47:40 by marvin            #+#    #+#             */
/*   Updated: 2024/01/29 19:47:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_settings.h"

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
	comp->player_colour = COMP_PLAYER_COLOR;
	comp->blur_on = BLUR_ON;
	comp->blur = (t_comp_blur){};
	comp->blur.max_kernel = BLUR_KERNEL_MAX;
	comp->blur.kernel_size = BLUR_KERNEL_SIZE;
	comp->blur.sigma = BLUR_KERNEL_SIGMA;
}

void	settings_compass(t_game *game, t_compass *comp)
{
	comp->centre = (t_pixel){COMP_CENTRE_X, COMP_CENTRE_Y, rgba(255, 0, 0, 0)};
	comp->radius = int_clamp(COMP_OUTER_RAD, COMP_MIN_RAD, COMP_MAX_RAD);
	comp->color = COMP_COLOR;
	comp->inner.radius = game->compass.radius * COMP_INNER_RAD_PERC;
	comp->inner.color = COMP_INNER_COLOR;
	comp->letter_radius = game->compass.radius * COMP_LETTER_RAD_PERC;
	comp->letter_width = game->compass.radius * COMP_LETTER_WDT_PERC;
	comp->letter_height = game->compass.radius * COMP_LETTER_HGT_PERC;
	comp->letter_color = COMP_LETTER_COLOR;
	comp->sqr_color = COMP_SQR_COLOR;
	comp->sqr_height = int_clamp (\
					(int)(game->compass.radius * SQR_HEIGHT_PERC), \
					(int)(game->compass.radius * SQR_MIN_HEIGHT_PERC), \
					(int)(game->compass.radius * SQR_MAX_HEIGHT_PERC));
	settings_compass_two(game, comp);
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
	settings_template_door(&game->template_door);
	settings_template_ammo(&game->template_ammo);
	settings_template_medi(&game->template_medi);
	settings_template_enemy(&game->template_enemy);
	settings_template_bullet(&game->template_bullet);
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
	game->rand.seed = 0;
	game->rand.clock = &game->clock;
	game->rand.multiplier = 1103515245;
	game->rand.increment = 12345;
}
