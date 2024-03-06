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

static inline void	fill_kernel_colors(t_pause_blur *blur, \
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

/*
	i hate x = -1 ++i, thanks norminette
*/
void	blur_horizontal(t_pause_blur *blur, char *dest, char *src, \
						t_blur_helper *help)
{
	int		blur_index;
	int		y;
	int		x;
	float	colors[4];
	int		i;

	y = blur->kernel_centre - 1;
	while (++y < help->height - blur->kernel_centre)
	{
		x = blur->kernel_centre - 1;
		while (++x < help->width - blur->kernel_centre)
		{
			blur_index = (y * help->width + x) * blur->rgb_size;
			ft_memset(colors, 0, sizeof(colors));
			i = -1;
			while (++i < blur->kernel_size)
			{
				blur->save_pixels[i] = *(int *)&src[(y * help->width + x \
					- blur->kernel_centre + i) * blur->rgb_size];
				fill_kernel_colors(blur, colors, i);
			}
			*(int *)&dest[blur_index] = pack_color_channels((int)colors[0], \
				(int)colors[1], (int)colors[2], (int)colors[3]);
		}
	}
}
