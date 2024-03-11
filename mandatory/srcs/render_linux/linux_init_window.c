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

#include "render_linux.h"

static int	init_mlx(t_win *win)
{
	win->mlx = mlx_init();
	if (!win->mlx)
		return (error_msg_int("cub3d: mlx failed to start\n", \
		STDERR_FILENO, 0));
	win->mlx_win = mlx_new_window(win->mlx, win->width, win->height, \
		win->name);
	if (!win->mlx_win)
		return (error_msg_int("cub3d: mlx window failed to open\n", \
		STDERR_FILENO, 0));
	win->front_buf.img = mlx_new_image(win->mlx, win->width, win->height);
	if (!win->front_buf.img)
		return (error_msg_int("cub3d: mlx image failed to start\n", \
		STDERR_FILENO, 0));
	win->front_buf.pixels = mlx_get_data_addr(win->front_buf.img, \
		&(win->front_buf.bpp), &(win->front_buf.line_len), \
		&(win->front_buf.endian));
	mlx_do_key_autorepeatoff(win->mlx);
	return (1);
}

int	win_init_window(t_win *win)
{
	if (!init_mlx(win))
		return (0);
	win->rgb_size = win->front_buf.bpp / 8;
	win->set_pixel = linux_set_pixel;
	win->get_pixel = linux_get_pixel;
	return (1);
}

int	free_window(t_win *win)
{
	if (win->front_buf.img)
		mlx_destroy_image(win->mlx, win->front_buf.img);
	if (win->mlx_win)
	{
		mlx_do_key_autorepeaton(win->mlx);
		mlx_destroy_window(win->mlx, win->mlx_win);
	}
	if (win->mlx)
	{
		mlx_destroy_display(win->mlx);
		free(win->mlx);
	}
	return (1);
}
