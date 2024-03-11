/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:41:48 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:41:48 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
duplicates a new string, copy using malloc
ft_strlen stops when finding a null byte... so we add
that null byte at the end when done as if we had copied it :)
we can use memcpy to copy byte by byte

*/

#include "ft_string.h"

char	*ft_strdup(t_cchar *s)
{
	int		len;
	char	*dest;

	len = ft_strlen(s);
	dest = malloc(sizeof(*dest) * (len + 1));
	if (!dest)
		return (perror_msg_ptr("malloc", NULL));
	ft_memcpy(dest, s, len);
	dest[len] = '\0';
	return (dest);
}
