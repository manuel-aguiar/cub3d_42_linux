/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:01:24 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:01:24 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strrchr(t_cchar *s, int c)
{
	t_cchar	*move;
	t_uchar	cc;

	cc = (t_uchar)c;
	move = s + ft_strlen(s);
	while (move > s && *move != cc)
		move--;
	if (*move == cc)
		return ((char *)move);
	return (NULL);
}
