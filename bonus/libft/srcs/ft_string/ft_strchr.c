/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:41:37 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:41:37 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strchr(t_cchar *s, int c)
{
	t_uchar	cc;

	cc = (t_uchar)c;
	while (*s && *s != cc)
		s++;
	if (*s || cc == '\0')
		return ((char *)s);
	return (NULL);
}
