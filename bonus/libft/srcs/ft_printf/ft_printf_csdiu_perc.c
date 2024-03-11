/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_csdiu_perc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 19:03:55 by manuel            #+#    #+#             */
/*   Updated: 2023/08/17 19:45:08 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	putcountint(int nb, int fd)
{
	char	str[11];
	char	print;
	int		i;
	char	sign;

	sign = 1;
	i = sizeof(str);
	if (nb < 0)
		sign = -1;
	if (nb == 0)
		str[--i] = '0';
	while (nb != 0)
	{
		print = nb % 10;
		if (print < 0)
			print *= -1;
		str[--i] = print + '0';
		nb /= 10;
	}
	if (sign == -1)
		str[--i] = '-';
	return (write(fd, &str[i], sizeof(str) - i));
}

int	putcountunint(unsigned int nb, int fd)
{
	char	str[11];
	int		i;

	i = sizeof(str);
	if (nb == 0)
		str[--i] = '0';
	while (nb != 0)
	{
		str[--i] = (nb % 10) + '0';
		nb /= 10;
	}
	return (write(fd, &str[i], sizeof(str) - i));
}

int	putcountstr(char *str, int fd)
{
	if (!str)
		return (putcountstr("(null)", fd));
	return (write(fd, str, ft_strlen(str)));
}

int	putcountchar(char c, int fd)
{
	return (write(fd, &c, 1));
}
