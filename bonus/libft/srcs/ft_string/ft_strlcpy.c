/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:17:28 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:17:28 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
similar to C03 (?) ft_strlcpy but with some changs which
appear to be more assembly friendly :). Move pointers as
much as possible instead of dereferencing with an iterator.
pre-decrement "size" because we need the final byte to be set
to null. Save start of the src in variable "st".
After copying, add the null byte at the nth byte or earlier if "src"
is over. If there is still source, keep looping to find it's null byte
Return: pointer difference between the starting location and the
null byte location.
*/

#include "ft_string.h"

size_t	ft_strlcpy(char *dst, t_cchar *src, size_t size)
{
	t_cchar	*st;

	st = src;
	if (size > 0)
	{
		while (--size > 0 && *src)
			*dst++ = *src++;
		*dst = '\0';
	}
	while (*src)
		src++;
	return ((size_t)(src - st));
}
