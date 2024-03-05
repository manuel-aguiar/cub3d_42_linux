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
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to transpose a square matrix represented as a 1D array
void transpose(int mat[], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            // Calculate indices in the 1D array
            int index1 = i * size + j;
            int index2 = j * size + i;
            swap(&mat[index1], &mat[index2]);
        }
    }
}

void	blur_compass(t_win *win, t_compass *comp)
{
	int		height;
	int		blur_index;
	int		img_x;
	int		img_y;
	int		y;
	int		x;
	float		colors[4];
	//int		radius_diff;
	t_blur	*blur;
	int rad_diff = comp->radius - comp->inner.radius;
	//radius_diff = comp->radius - comp->inner.radius;
	blur = &comp->blur;
	height = blur->blur_height;
	img_x = (comp->centre.x - comp->radius);
	img_y = (comp->centre.y - comp->radius);
	int centre = blur->kernel_size / 2;
	y = 0;
	while (y < height)
	{
		if (y >= comp->inner.min_max[MM_MIN_Y] + comp->radius - centre \
		&& y < comp->inner.min_max[MM_MAX_Y] + comp->radius + centre \
		&& y >= rad_diff && y < height  - rad_diff )
		{
			x = 0;
			while (x < height)
			{
				blur_index = y * height + x;
				if (x >= comp->circle_x_lim[y - rad_diff].min + comp->radius - centre && x <= comp->circle_x_lim[y - rad_diff].max + comp->radius + centre)
				{
					ft_memset(colors, 0, sizeof(colors));
					int i;
					i = 0;					
					while (i < blur->kernel_size)
					{
						blur->save_pixels[i] = win->get_pixel(win, (x + img_x) - centre + i, (y + img_y));
						colors[0] += rgb_r(blur->save_pixels[i]) * blur->kernel[i];
						colors[1] += rgb_g(blur->save_pixels[i]) * blur->kernel[i];
						colors[2] += rgb_b(blur->save_pixels[i]) * blur->kernel[i];
						colors[3] += rgb_a(blur->save_pixels[i]) * blur->kernel[i];
						i++;
					}
					blur->hori_blur[blur_index] = rgba((int)(colors[0]), (int)(colors[1]), (int)(colors[2]), (int)(colors[3]));
				}
				x++;
			}
		}
		y++;
	}
	transpose(blur->hori_blur, height);
	y = blur->kernel_size / 2;
	while ( y < height - blur->kernel_size / 2)
	{
		if (y >= comp->inner.min_max[MM_MIN_Y] + comp->radius && y < comp->inner.min_max[MM_MAX_Y] + comp->radius)
		{
			x = blur->kernel_size / 2;
			while (x < height - blur->kernel_size / 2)
			{
				blur_index = y * height + x;
				if (x >= comp->circle_x_lim[y - rad_diff].min + comp->radius && x <= comp->circle_x_lim[y - rad_diff].max + comp->radius)
				{
					ft_memset(colors, 0, sizeof(colors));
					int i;
					i = 0;
					while (i < blur->kernel_size)
					{
						blur->save_pixels[i] = blur->hori_blur[blur_index - centre + i];
						colors[0] += rgb_r(blur->save_pixels[i]) * blur->kernel[i];
						colors[1] += rgb_g(blur->save_pixels[i]) * blur->kernel[i];
						colors[2] += rgb_b(blur->save_pixels[i]) * blur->kernel[i];
						colors[3] += rgb_a(blur->save_pixels[i]) * blur->kernel[i];
						i++;
					}
					blur->verti_blur[blur_index] = rgba((int)(colors[0]), (int)(colors[1]), (int)(colors[2]), (int)(colors[3]));
				}
				x++;
			}
		}
		y++;
	}	
	transpose(blur->verti_blur, height);
}
