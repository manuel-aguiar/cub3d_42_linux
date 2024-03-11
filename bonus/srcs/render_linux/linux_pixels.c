/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_set_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 10:41:56 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 10:41:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_linux.h"

/*
endianess issues here, should place pixels char by char....
performance looks to be exactly the same, optimized by the compiler

*/

void	linux_set_pixel(t_win *win, int x, int y, int color)
{
	char	*dst;

	y = win->height - y - 1;
	dst = win->front_buf.pixels + (y * win->front_buf.line_len + \
		x * (win->front_buf.bpp / 8));
	*(unsigned int *)dst = color;
}

int	linux_get_pixel(t_win *win, int x, int y)
{
	char	*dst;

	y = win->height - y - 1;
	dst = win->front_buf.pixels + (y * win->front_buf.line_len + \
		x * (win->front_buf.bpp / 8));
	return (*(unsigned int *)dst);
}

void	swap_pixels(t_pixel *start, t_pixel *end)
{
	t_pixel	temp;

	temp = *start;
	*start = *end;
	*end = temp;
}
