/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:22:59 by marvin            #+#    #+#             */
/*   Updated: 2023/05/29 11:22:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	check_base(char *base, int *baselen)
{
	int	i;
	int	j;

	i = 0;
	while (base[i])
	{
		j = 0;
		while (j < i)
		{
			if (ft_tolower(base[j]) == ft_tolower(base[i]))
				return (0);
			j++;
		}
		i++;
	}
	if (i <= 1)
		return (0);
	*baselen = i;
	return (1);
}

static int	in_base(int *res, char c, char *base, int baselen)
{
	int	i;

	i = 0;
	while ((i < baselen))
	{
		if (ft_tolower(c) == ft_tolower(base[i]))
		{
			*res = i;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_atoi_base(char *str, char *base)
{
	int	baselen;
	int	res;
	int	sign;
	int	cur;

	if (!check_base(base, &baselen))
		return (0);
	sign = 1;
	while (*str && ft_isspace(*str))
		str++;
	if (*str == '-')
		sign = -1;
	if (*str == '-' || *str == '+')
		str++;
	res = 0;
	while (in_base(&cur, *str++, base, baselen))
		res = res * baselen + cur;
	return (res * sign);
}

/*
#include <stdio.h>
#define HEX "0123456789abcdef"
int main(int ac, char **av)
{
	if (ac == 3)
		printf("number is %d\n", ft_atoi_base(av[1], av[2]));
	return (0);
}*/
