/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:20:02 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:20:02 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_atoi.h"

static int	numdigits(int nb)
{
	int	i;

	if (nb == 0)
		return (1);
	i = 0;
	while (nb != 0)
	{
		i++;
		nb /= 10;
	}
	return (i);
}

static void	stringit(char *str, int nb, int len)
{
	int	mod;

	str[len--] = '\0';
	if (nb == 0)
		str[0] = '0';
	else
	{
		while (nb != 0)
		{
			mod = nb % 10;
			if (mod < 0)
				mod *= -1;
			str[len] = mod + '0';
			len--;
			nb /= 10;
		}
	}
}

char	*ft_itoa(int nb)
{
	int		len;
	char	*str;

	len = 0;
	if (nb < 0)
		len++;
	len += numdigits(nb);
	str = malloc(sizeof(*str) * (len + 1));
	if (!str)
		return (perror_msg_ptr("malloc", NULL));
	if (nb < 0)
		str[0] = '-';
	stringit(str, nb, len);
	return (str);
}
