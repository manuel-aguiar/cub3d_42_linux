/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:28:25 by manuel            #+#    #+#             */
/*   Updated: 2023/04/18 17:53:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

int	ft_strncmp(t_cchar *s1, t_cchar *s2, size_t n)
{
	t_cchar	*str1;
	t_cchar	*str2;

	str1 = (t_cchar *)s1;
	str2 = (t_cchar *)s2;
	if (n == 0)
		return (0);
	while (--n && (*str1 || *str2) && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	return (*str1 - *str2);
}
