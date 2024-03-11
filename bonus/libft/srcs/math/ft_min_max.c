/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:15:43 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/08/27 18:16:03 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

int	ft_abs(int num)
{
	return (ft_ternary(num > 0, num, -num));
}

int	ft_min(int first, int second)
{
	if (first > second)
		return (second);
	return (first);
}

int	ft_max(int first, int second)
{
	if (first > second)
		return (first);
	return (second);
}

float	ft_fmin(float first, float second)
{
	if (first < second)
		return (first);
	return (second);
}

float	ft_fmax(float first, float second)
{
	if (first > second)
		return (first);
	return (second);
}
