/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:28:25 by manuel            #+#    #+#             */
/*   Updated: 2024/03/07 10:48:57 by codespace        ###   ########.fr       */
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
