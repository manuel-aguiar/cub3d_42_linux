/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:38:02 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 20:38:02 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

size_t	ft_strlcat(char *dst, t_cchar *src, size_t size)
{
	char		*d;
	t_cchar		*s;
	size_t		n;
	size_t		destlen;

	d = dst;
	s = src;
	n = size;
	while (n-- != 0 && *d != '\0')
		d++;
	destlen = d - dst;
	n = size - destlen;
	if (n == 0)
		return (destlen + ft_strlen(s));
	while (*s)
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (destlen + (s - src));
}

/*
#include <stdio.h>
int	main(void)
{
	char src[] = " man";
	char dest1[10] = "yaaa";
	char dest3[10] = "yaaa";

	printf("my func: %s  %ld\n", dest1, ft_strlcat(dest1, src, 4));


	return (0);
}*/
