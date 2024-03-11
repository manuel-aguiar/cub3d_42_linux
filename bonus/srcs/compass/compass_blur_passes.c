/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass_blur_passes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 17:48:53 by codespace         #+#    #+#             */
/*   Updated: 2024/03/11 13:40:50 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compass.h"

static inline void	fill_kernel_colors(t_comp_blur *blur, \
					float colors[4], int index)
{
	colors[0] += ((blur->save_pixels[index] >> 24) & 0xff) \
		* blur->kernel[index];
	colors[1] += ((blur->save_pixels[index] >> 16) & 0xff) \
		* blur->kernel[index];
	colors[2] += ((blur->save_pixels[index] >> 8) & 0xff) \
		* blur->kernel[index];
	colors[3] += ((blur->save_pixels[index] >> 0) & 0xff) \
		* blur->kernel[index];
}

static inline void	second_pass_helper(t_comp_blur *blur, int blur_index)
{
	float		colors[4];
	int			i;

	ft_memset(colors, 0, sizeof(colors));
	i = 0;
	while (i < blur->kernel_size)
	{
		blur->save_pixels[i] = blur->hori_blur[blur_index \
			- blur->centre + i];
		fill_kernel_colors(blur, colors, i);
		i++;
	}
	blur->verti_blur[blur_index] = pack_color_channels((int)(colors[0]), \
		(int)(colors[1]), (int)(colors[2]), (int)(colors[3]));
}

void	second_pass(t_compass *comp, t_comp_blur *blur)
{
	int			blur_index;
	int			y;
	int			x;

	blur = &comp->blur;
	y = blur->centre;
	while (y < blur->blur_height - blur->centre)
	{
		if (y >= comp->inner.min_max[MM_MIN_Y] + comp->radius \
		&& y < comp->inner.min_max[MM_MAX_Y] + comp->radius)
		{
			x = blur->centre;
			while (x < blur->blur_height - blur->centre)
			{
				blur_index = y * blur->blur_height + x;
				if (x >= comp->circle_x_lim[y - blur->rad_diff].min \
					+ comp->radius \
				&& x <= comp->circle_x_lim[y - blur->rad_diff].max \
					+ comp->radius)
					second_pass_helper(blur, blur_index);
				x++;
			}
		}
		y++;
	}
}

static inline void	first_pass_helper(t_win *win, t_comp_blur *blur, \
									int x, int y)
{
	int		i;
	int		blur_index;
	float	colors[4];

	blur_index = y * blur->blur_height + x;
	ft_memset(colors, 0, sizeof(colors));
	i = 0;
	while (i < blur->kernel_size)
	{
		blur->save_pixels[i] = win->get_pixel(win, \
			(x + blur->img_x) - blur->centre + i, (y + blur->img_y));
		fill_kernel_colors(blur, colors, i);
		i++;
	}
	blur->hori_blur[blur_index] = pack_color_channels(\
		(int)(colors[0]), (int)(colors[1]), (int)(colors[2]), \
		(int)(colors[3]));
}

void	first_pass(t_win *win, t_compass *comp, t_comp_blur	*blur)
{
	int			y;
	int			x;

	y = 0;
	while (y < blur->blur_height)
	{
		if (y >= comp->inner.min_max[MM_MIN_Y] + comp->radius - blur->centre \
		&& y < comp->inner.min_max[MM_MAX_Y] + comp->radius + blur->centre \
		&& y >= blur->rad_diff && y < blur->blur_height - blur->rad_diff)
		{
			x = 0;
			while (x < blur->blur_height)
			{
				if (x >= comp->circle_x_lim[y - blur->rad_diff].min \
					+ comp->radius - blur->centre \
				&& x <= comp->circle_x_lim[y - blur->rad_diff].max \
					+ comp->radius + blur->centre)
					first_pass_helper(win, blur, x, y);
				x++;
			}
		}
		y++;
	}
}
