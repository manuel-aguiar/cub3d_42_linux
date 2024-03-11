/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_arr.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:35:18 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 17:35:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
Transform command line arguments to an integer array. If at least one argv[i]
can't be converted, arr is freed. Returns length of the int array, or zero if
conversion of at least one of argv[i] fails. User input, ac is the max of
integers converted. If user ac = -1, fuction gets the length of av and converts
all to integers, if possible. (av must be null terminated in that case).

the return value is zero if malloc fails or one of the inputs overflows
the integer. In this case, the location where the array would eb placed
is set to NULL for safety

returns the size of the array that was created when it is successfull which
can be asigned to a variable for safe array manipulation.

*/

#include "ft_atoi.h"
#include <stddef.h>

int	atoi_overf(int res, char next, int *sign);

static int	ft_argv_count(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	ft_atoiable(char *str, int *placenum)
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
	if (!ft_isdigit(*str))
		sign = 0;
	res = 0;
	while (*str && ft_isdigit(*str) && atoi_overf(res, *str, &sign))
		res = res * 10 - '0' + *str++;
	*placenum = res * sign;
	if (sign == 0)
		return (0);
	return (1);
}

static int	*atoi_arr_malloc(int *ac, char **av, int *status)
{
	int	avlen;
	int	*arr;

	arr = NULL;
	avlen = ft_argv_count(av);
	if (*ac == 0 || !avlen)
	{
		*status = 0;
		*ac = 0;
	}
	if (*status)
	{
		if (*ac == -1)
			*ac = avlen;
		if (*ac < avlen)
			avlen = *ac;
		arr = malloc(sizeof(*arr) * avlen);
		if (arr)
			*ac = avlen;
		else
			*status = 0;
	}
	return (arr);
}

int	ft_atoi_arr(int **dest, int ac, char **av)
{
	int	*arr;
	int	num;
	int	status;
	int	i;

	status = 1;
	arr = atoi_arr_malloc(&ac, av, &status);
	if (arr && status)
	{
		i = 0;
		while (i < ac && status)
		{
			if (ft_atoiable(av[i], &num))
				arr[i++] = num;
			else
			{
				status = 0;
				free (arr);
				arr = NULL;
			}
		}
	}
	*dest = arr;
	return (ac * status);
}
