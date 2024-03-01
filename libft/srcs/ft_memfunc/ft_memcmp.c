/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:28:25 by manuel            #+#    #+#             */
/*   Updated: 2023/04/18 17:55:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memfunc.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	t_uchar	*str1;
	t_uchar	*str2;

	str1 = (t_uchar *)s1;
	str2 = (t_uchar *)s2;
	if (n == 0)
		return (0);
	while (--n && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}

/*
int main (void)
{
	//printf("memcmp %d\n", ft_memcmp ("ola tudo bem", "ola tudo bem", 10000000));
	printf("memcmp %d\n", ft_memcmp("abcdefghij", "abcdefgxyz", 7));
}*/
