/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liang_barsky_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:45:29 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:45:29 by mmaria-d         ###   ########.fr       */
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
