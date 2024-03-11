/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 14:44:46 by marvin            #+#    #+#             */
/*   Updated: 2024/02/29 14:44:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generic_utils.h"

void	int_swap(int *first, int *second)
{
	int	swap;

	swap = *first;
	*first = *second;
	*second = swap;
}

void	float_swap(float *first, float *second)
{
	float	swap;

	swap = *first;
	*first = *second;
	*second = swap;
}
