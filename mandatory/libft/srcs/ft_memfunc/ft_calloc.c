/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:45:42 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 14:45:42 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
creates a new array with malloc and sets all BYTES to zero.
essentially malloc + bzero. here we replace memset to avoid the
specific call to bzero. memset byte size is "number of members"
time "size of each member", precisely because memset sets BYTES
and since calloc requires full size, we can do send it safely:
caller is responsible for providing the correct number of elements
and the correct size of each with sizeof
*/

#include "ft_memfunc.h"

void	*ft_calloc(size_t nmemb, size_t bytes)
{
	void	*new;

	new = malloc(nmemb * bytes);
	if (!new)
		return (perror_msg_ptr("malloc", NULL));
	ft_memset(new, 0, nmemb * bytes);
	return (new);
}
