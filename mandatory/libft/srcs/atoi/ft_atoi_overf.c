/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_overf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:29:46 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 17:29:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_atoi.h"

#include <limits.h>

int	atoi_overf(int res, char next, int *sign)
{
	int	max;

	max = INT_MAX / 10;
	if (res < max)
		return (1);
	if (res > max)
	{
		*sign = 0;
		return (0);
	}
	else if (res == max)
	{
		if (*sign == 1 && next > INT_MAX % 10 + '0')
		{
			*sign = 0;
			return (0);
		}
		if (*sign == -1 && next > -(INT_MIN % 10) + '0')
		{
			*sign = 0;
			return (0);
		}
	}
	return (1);
}

int	ft_atoi_overf(char *str)
{
	int	res;
	int	sign;

	while (*str && ft_isspace(*str))
		str++;
	sign = 1;
	if (*str && *str == '-')
		sign = -1;
	if (*str && (*str == '-' || *str == '+'))
		str++;
	res = 0;
	while (*str && ft_isdigit(*str) && atoi_overf(res, *str, &sign))
		res = res * 10 - '0' + *str++;
	if (sign == 0)
		res = 0;
	return (res * sign);
}
