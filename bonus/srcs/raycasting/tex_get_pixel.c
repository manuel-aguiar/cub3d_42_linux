/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_get_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:56:49 by codespace         #+#    #+#             */
/*   Updated: 2024/03/11 13:39:28 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	tex_get_pixel(t_win *win, t_mlx_img *tex, int index)
{
	char	*dst;

	dst = &tex->pixels[index * win->rgb_size];
	return (*(unsigned int *)dst);
}
