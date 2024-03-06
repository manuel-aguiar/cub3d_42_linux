/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:26:48 by codespace         #+#    #+#             */
/*   Updated: 2024/03/06 12:28:03 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixel_point.h"

int	argb(int color)
{
	int	new;

	new = ((color & 0xff) << 24) \
	| (((color >> 8) & 0xff) << 16) \
	| (((color >> 16) & 0xff) << 8) \
	| ((color >> 24) & 0xff);
	return (new);
}

int	abgr_inversion(int r, int g, int b, int a)
{
	return ((a << 24) | (b << 16) | (g << 8) | (r));
}

int	pack_color_channels(int fst, int snd, int trd, int fth)
{
	return ((fst << 24) | (snd << 16) | (trd << 8) | (fth));
}

int	avg_colour(int start, int end, int num, int den)
{
	t_ulong	r;
	t_ulong	g;
	t_ulong	b;
	t_ulong	a;

	if (den == 0)
		return (start);
	r = rgb_r(start) * num / den \
		+ rgb_r(end) * (den - num) / den;
	g = rgb_g(start) * num / den \
		+ rgb_g(end) * (den - num) / den;
	b = rgb_b(start) * num / den \
		+ rgb_b(end) * (den - num) / den;
	a = rgb_a(start);
	return (pack_color_channels((int)r, (int)g, (int)b, (int)a));
}
