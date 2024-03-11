/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:14:06 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:14:06 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

char	*ft_substr(t_cchar *s, t_uint start, size_t len)
{
	char	*new;
	size_t	og_len;
	size_t	new_len;

	og_len = ft_strlen(s);
	if (og_len < len + start)
		new_len = og_len - start;
	else
		new_len = len;
	if (start > og_len || len == 0)
		new_len = 0;
	new = malloc(sizeof(*new) * (new_len + 1));
	if (!new)
		return (perror_msg_ptr("malloc", NULL));
	ft_memcpy(new, &s[start], new_len);
	new[new_len] = '\0';
	return (new);
}
