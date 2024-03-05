/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_get_pixel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:56:49 by codespace         #+#    #+#             */
/*   Updated: 2024/03/05 12:07:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int		tex_get_pixel(t_win *win, t_xpm_tex *tex, int index)
{
	char		*dst;

	dst = &tex->pixels[index * win->front_buf.bpp / 8];
	return (*(unsigned int *)dst);
}
