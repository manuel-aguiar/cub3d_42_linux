/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_equal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 15:28:47 by marvin            #+#    #+#             */
/*   Updated: 2024/03/11 13:42:55 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generic_utils.h"

bool	float_equal(float num, float target, float error)
{
	if (ft_fabs(num - target) <= error)
		return (1);
	return (0);
}
