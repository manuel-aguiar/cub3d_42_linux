/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_lb_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 14:41:20 by marvin            #+#    #+#             */
/*   Updated: 2023/07/21 14:41:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawing_algos.h"

float	lb_maxi(float arr[], int n)
{
	float	m;
	int		i;

	m = 0;
	i = 0;
	while (i < n)
	{
		if (m < arr[i])
			m = arr[i];
		i++;
	}
	return (m);
}

float	lb_mini(float arr[], int n)
{
	float	m;
	int		i;

	m = 1;
	i = 0;
	while (i < n)
	{
		if (m > arr[i])
			m = arr[i];
		i++;
	}
	return (m);
}
