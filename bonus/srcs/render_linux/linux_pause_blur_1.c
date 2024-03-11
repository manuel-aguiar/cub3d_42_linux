/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_pause_blur_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:28:48 by marvin            #+#    #+#             */
/*   Updated: 2024/02/29 14:28:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "render_linux.h"

int		window_update_clock(t_win *win);
void	blur_horizontal(t_pause_blur *blur, char *dest, char *src, \
						t_blur_helper *help);

void	window_transpose(char *dest, char *src, t_blur_helper *help)
{
	int	row;
	int	col;
	int	src_index;
	int	dest_index;

	row = 0;
	while (row < help->height)
	{
		col = 0;
		while (col < help->width)
		{
			src_index = (col + row * help->width) * help->rgb_size;
			dest_index = (row + col * help->height) * help->rgb_size;
			*(int *)(&dest[dest_index]) = *(int *)(&src[src_index]);
			col++;
		}
		row++;
	}
}

void	dump_blur_to_front_buf(t_win *win, t_pause_blur *blur, char *dump)
{
	int	y;
	int	index;
	int	size;

	y = blur->kernel_centre;
	while (y < win->height - blur->kernel_centre)
	{
		index = (blur->kernel_centre + y * win->width) \
			* win->rgb_size;
		size = (win->width - (int)(blur->kernel_size / 2) * 2) \
			* win->rgb_size;
		ft_memcpy(&win->front_buf.pixels[index], &dump[index], size);
		y++;
	}
}

static float	pause_gaussian(float x, float sigma)
{
	return (exp(-(x * x) / (2 * sigma * sigma)) / (sqrt(2 * MY_PI) * sigma));
}

static void	pause_setup_kernel(t_pause_blur *blur)
{
	int		i;
	float	sum;

	sum = 0;
	i = 0;
	while (i < blur->kernel_size)
	{
		blur->kernel[i] = pause_gaussian(i - blur->kernel_centre, \
			sqrt(blur->cur_sigma));
		sum += blur->kernel[i];
		i++;
	}
	i = 0;
	while (i < blur->kernel_size)
	{
		blur->kernel[i] /= sum;
		i++;
	}
}

void	blur_pause(t_win *win, t_pause_blur *blur, bool increase_blur)
{
	t_blur_helper	help;

	if (increase_blur)
		blur->elapsed = int_clamp(blur->elapsed + window_update_clock(win), \
			0, blur->pause_time);
	else
		blur->elapsed = int_clamp(blur->elapsed - window_update_clock(win), \
			0, blur->pause_time);
	blur->cur_sigma = blur->min_sigma + (int)(((float)blur->elapsed \
		/ (float)blur->pause_time) * (blur->max_sigma - blur->min_sigma));
	pause_setup_kernel(blur);
	help = (t_blur_helper){blur->width, blur->height, blur->rgb_size};
	blur_horizontal(blur, blur->first, blur->save_front, &help);
	window_transpose(blur->second, blur->first, &help);
	help = (t_blur_helper){blur->height, blur->width, blur->rgb_size};
	blur_horizontal(blur, blur->first, blur->second, &help);
	window_transpose(blur->second, blur->first, &help);
	dump_blur_to_front_buf(win, blur, blur->second);
}
