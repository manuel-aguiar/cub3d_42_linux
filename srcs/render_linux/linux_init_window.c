/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_window.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:13:01 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 10:13:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "render_linux.h"

int	win_init_window(t_win *win)
{
	win->mlx = mlx_init();
	if (!win->mlx)
		return (error_msg_int("cub3d: mlx failed to initialize\n", STDERR_FILENO, 0));
	win->mlx_win = mlx_new_window(win->mlx, win->width, win->height, win->name);
	win->front_buf.img = mlx_new_image(win->mlx, win->width, win->height);
	win->front_buf.addr = mlx_get_data_addr(win->front_buf.img, \
		&(win->front_buf.bpp), &(win->front_buf.line_len), \
		&(win->front_buf.endian));
	win->rgb_size = win->front_buf.bpp / 8;
	win->blur.first = malloc(sizeof(*win->blur.first) * win->width * win->height * win->rgb_size);
	win->blur.second = malloc(sizeof(*win->blur.second) * win->width * win->height * win->rgb_size);
	win->blur.save_front = malloc(sizeof(*win->blur.save_front) * win->width * win->height * win->rgb_size);
	win->blur.clock = (t_clock){};
	gettimeofday(&win->blur.clock.start, NULL);
	if (!win->front_buf.img || !win->blur.first || !win->blur.second || !win->blur.save_front)
		return (perror_msg_int("malloc", 0));
	win->set_pixel = linux_set_pixel;
	win->get_pixel = linux_get_pixel;
	mlx_do_key_autorepeatoff(win->mlx);
	mlx_mouse_hide(win->mlx, win->mlx_win);
	return (1);	
}

int	free_window(t_win *win)
{

	if (win->front_buf.img)
		mlx_destroy_image(win->mlx, win->front_buf.img);
	if (win->mlx_win)
		mlx_destroy_window(win->mlx, win->mlx_win);
	if (win->mlx)
	{
		mlx_destroy_display(win->mlx);
		mlx_do_key_autorepeaton(win->mlx);
		mlx_mouse_show(win->mlx, win->mlx_win);
	}
	if (win->blur.first)
		free(win->blur.first);
	if (win->blur.second)
		free(win->blur.second);
	if (win->blur.save_front)
		free(win->blur.save_front);
	return (1);
}
