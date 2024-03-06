/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blur.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 11:29:55 by marvin            #+#    #+#             */
/*   Updated: 2024/02/16 11:29:55 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "compass.h"

/*
	Prepare blur with a fixed kernel 1,4,6,4,1 (normalized is aproximatelly gaussian)

	Do horizontal pass and then vertical, not cache optimal but i don't want to transpose
*/

void	transpose_square_matrix(int *mat, int size)
{
	int	i;
	int	j;
	int	index1;
	int	index2;

	i = 0;
    while (i < size)
	{
		j = i + 1;
        while (j < size)
		{
            index1 = i * size + j;
            index2 = j * size + i;
            int_swap(&mat[index1], &mat[index2]);
			j++;
        }
		i++;
    }
}

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

typedef struct s_render_blur
{
	t_comp_blur	*blur;
	int			height;
	int			blur_index;
	int			img_x;
	int			img_y;
}	t_render_blur;

void	blur_compass(t_win *win, t_compass *comp)
{
	int			height;
	int			blur_index;
	int			y;
	int			x;
	int 		i;
	float		colors[4];
	t_comp_blur	*blur;


	blur = &comp->blur;
	height = blur->blur_height;
	y = 0;
	while (y < height)
	{
		if (y >= comp->inner.min_max[MM_MIN_Y] + comp->radius - blur->centre \
		&& y < comp->inner.min_max[MM_MAX_Y] + comp->radius + blur->centre \
		&& y >= blur->rad_diff && y < height - blur->rad_diff)
		{
			x = 0;
			while (x < height)
			{
				blur_index = y * height + x;
				if (x >= comp->circle_x_lim[y - blur->rad_diff].min + comp->radius - blur->centre \
				&& x <= comp->circle_x_lim[y - blur->rad_diff].max + comp->radius + blur->centre)
				{
					ft_memset(colors, 0, sizeof(float) * 4);

					i = 0;
					while (i < blur->kernel_size)
					{
						blur->save_pixels[i] = win->get_pixel(win, (x + blur->img_x) - blur->centre + i, (y + blur->img_y));
						fill_kernel_colors(blur, colors, i);
						i++;
					}
					blur->hori_blur[blur_index] = pack_color_channels((int)(colors[0]), (int)(colors[1]), (int)(colors[2]), (int)(colors[3]));
				}
				x++;
			}
		}
		y++;
	}
	transpose_square_matrix(blur->hori_blur, height);
	y = blur->centre;
	while ( y < height - blur->centre)
	{
		if (y >= comp->inner.min_max[MM_MIN_Y] + comp->radius \
		&& y < comp->inner.min_max[MM_MAX_Y] + comp->radius)
		{
			x = blur->centre;
			while (x < height - blur->centre)
			{
				blur_index = y * height + x;
				if (x >= comp->circle_x_lim[y - blur->rad_diff].min + comp->radius \
				&& x <= comp->circle_x_lim[y - blur->rad_diff].max + comp->radius)
				{
					ft_memset(colors, 0, sizeof(float) * 4);
					i = 0;
					while (i < blur->kernel_size)
					{
						blur->save_pixels[i] = blur->hori_blur[blur_index - blur->centre + i];
						fill_kernel_colors(blur, colors, i);
						i++;
					}
					blur->verti_blur[blur_index] = rgba((int)(colors[0]), (int)(colors[1]), (int)(colors[2]), (int)(colors[3]));
				}
				x++;
			}
		}
		y++;
	}
	transpose_square_matrix(blur->verti_blur, height);
}
