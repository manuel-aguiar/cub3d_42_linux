/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:44:25 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 18:44:25 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pixel_point.h"

int	rgb_a(int color)
{
	return ((color >> 24) & 0xff);
}

int	rgb_r(int color)
{
	return ((color >> 16) & 0xff);
}

int	rgb_g(int color)
{
	return ((color >> 8) & 0xff);
}

int	rgb_b(int color)
{
	return (color & 0xff);
}

int	rgba(int r, int g, int b, int a)
{
	return ((a << 24) | (r << 16) | (g << 8) | (b));
}

/*
int	avg_colour_new(int start, int end, int num, int den)
{
	int		new;
	char	*p_new;
	char	*p_start;
	char	*p_end;

	if (den == 0)
		return (start);
	p_new = (char *)&new;
	p_start = (char *)&start;
	p_end = (char *)&end;
	p_new[0] = p_start[0] * num / den + p_end[0] * (den - num) / den;
	p_new[1] = p_start[1] * num / den + p_end[1] * (den - num) / den;
	p_new[2] = p_start[2] * num / den + p_end[2] * (den - num) / den;
	p_new[3] = p_start[3] * num / den + p_end[3] * (den - num) / den;
	return (new);
}


int	avg_colour_3(int start, int end, int num, int den)
{
	int		i;
    int     new;
	char	*ptr_new;
	char	pix_start;
	char	pix_end;

    if (den == 0)
		return (start);
    ptr_new = (char *)&new;
	i = 0;
	while (i < 4)
	{
		pix_start = ((start >> (i * 8)) & 0xff);
		pix_end = ((end >> (i * 8)) & 0xff);
		ptr_new[i] = (char)(pix_start * num / den + pix_end * (den - num) / den);
		i++;
	}
	return (*(int *)ptr_new);
}
*/
