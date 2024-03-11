/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:20:38 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:20:38 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memfunc.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	t_uchar	*move;
	t_uchar	cc;

	if (n == 0)
		return (NULL);
	cc = (t_uchar)c;
	move = (t_uchar *)s;
	while (--n && *move != cc)
		move++;
	if (*move == cc)
		return (move);
	return (NULL);
}
