/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_pause_blur.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/19 12:33:24 by marvin            #+#    #+#             */
/*   Updated: 2024/02/19 12:33:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_linux.h"

void	blur_pause(t_win *win, t_pause_blur *blur, bool increase_blur);

int	window_update_clock(t_win *win)
{
	gettimeofday(&win->blur.clock.end, NULL);
	win->blur.clock.elapsed = (size_t)((win->blur.clock.end.tv_sec \
		- win->blur.clock.start.tv_sec) * 1000 \
		+(win->blur.clock.end.tv_usec - win->blur.clock.start.tv_usec) / 1000);
	win->blur.clock.start = win->blur.clock.end;
	return (win->blur.clock.elapsed + 1);
}

void	mouse_hide_and_centre(t_win *win)
{
	mlx_mouse_hide(win->mlx, win->mlx_win);
	mlx_mouse_move(win->mlx, win->mlx_win, win->width / 2, win->height / 2);
	win->mouse.cur_x = win->width / 2;
	win->mouse.cur_y = win->height / 2;
}

int	window_pause_on(t_win *win, t_pause_blur *blur, bool blur_on)
{
	if (blur->elapsed >= blur->pause_time)
	{
		blur->elapsed = blur->pause_time;
		return (0);
	}
	if (blur->elapsed <= 0)
	{
		ft_memcpy(blur->save_front, win->front_buf.pixels, win->height \
			* win->width * win->rgb_size);
		window_update_clock(win);
		blur->elapsed = 1;
		mlx_mouse_show(win->mlx, win->mlx_win);
	}
	if (blur_on)
		blur_pause(win, blur, true);
	else
		blur->elapsed = int_clamp(blur->elapsed \
			+ window_update_clock(win), 0, blur->pause_time);
	return (1);
}

int	window_pause_off(t_win *win, t_pause_blur *blur, bool blur_on)
{
	if (blur->elapsed <= 0)
	{
		blur->elapsed = 0;
		mouse_hide_and_centre(win);
		return (0);
	}
	if (blur->elapsed >= blur->pause_time)
	{
		blur->elapsed = blur->pause_time;
		window_update_clock(win);
	}
	if (blur_on)
		blur_pause(win, blur, false);
	else
		blur->elapsed = int_clamp(blur->elapsed \
			- window_update_clock(win), 0, blur->pause_time);
	if (blur->elapsed == 0)
		mouse_hide_and_centre(win);
	return (1);
}

void	window_pause_manager(t_win *win, t_pause_state state, bool blur_on)
{
	t_pause_blur	*blur;

	blur = &win->blur;
	if (state == PAUSE_ON)
		window_pause_on(win, blur, blur_on);
	else if (state == PAUSE_OFF)
		window_pause_off(win, blur, blur_on);
}
