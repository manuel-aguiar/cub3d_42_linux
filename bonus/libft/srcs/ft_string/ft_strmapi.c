/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:14:39 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:14:39 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_strmapi(char *s, char (*f)(t_uint, char))
{
	t_uint		len;
	t_uint		i;
	char		*new;

	if (!s)
		return (NULL);
	len = ft_strlen(s);
	new = malloc(sizeof(*new) * (len + 1));
	if (!new)
		return (perror_msg_ptr("malloc", NULL));
	i = 0;
	while (i < len)
	{
		new[i] = f(i, s[i]);
		i++;
	}
	new[len] = '\0';
	return (new);
}
