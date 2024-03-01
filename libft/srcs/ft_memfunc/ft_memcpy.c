/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:53:30 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 14:53:30 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* memcpy is the strictly left to right version of memmove
if dest and src, there may be undefined behavior in case dest > src.
As with the "mem" functions, memcpy copies BYTES, so it is up to the caller
to do the math in case the arrays involved are made of elements of
different size.
looks similar to the memcpy.c implementation, it takes less assembly
operations vs using an iterator i and dereferencing locations
(even taking into account we are decreasing n and incrementing both pointers
instead of moving "i" all in one)*/

#include "ft_memfunc.h"

static size_t	check_align(t_uchar **dest, t_uchar **src, size_t *len)
{
	t_ulong	check;

	while (((t_ulong)(*dest) & UL_ALIGN) != 0)
	{
		*(*dest)++ = *(*src)++;
		(*len)--;
	}
	check = ((t_ulong)(*src) & UL_ALIGN);
	if (check != 0)
	{
		*src += (UL_SIZE - check);
		return (check);
	}
	return (0);
}

static void	loop_unroll(t_ulong **dest, t_ulong **src, size_t chunk,
		size_t roll)
{
	if (roll == FOUR_UNROLL)
	{
		while (chunk--)
		{
			(*dest)[0] = (*src)[0];
			(*dest)[1] = (*src)[1];
			(*dest)[2] = (*src)[2];
			(*dest)[3] = (*src)[3];
			*dest += 4;
			*src += 4;
		}
	}
	else
	{
		while (chunk--)
		{
			(*dest)[0] = (*src)[0];
			(*dest)[1] = (*src)[1];
			*dest += 2;
			*src += 2;
		}
	}
}

static size_t	misalign_copy(t_ulong **dest, t_ulong **src, size_t len,
		size_t bytedif)
{
	size_t	chunk_len;
	t_uchar	lbytes;
	t_uchar	rbytes;

	(*src)--;
	lbytes = (bytedif * CHAR_BIT);
	rbytes = (UL_SIZE * CHAR_BIT) - lbytes;
	chunk_len = (len / (UL_SIZE * TWO_UNROLL));
	len %= (UL_SIZE * TWO_UNROLL);
	while (chunk_len--)
	{
		(*dest)[0] = (((*src)[0] >> lbytes) | ((*src)[1] << rbytes));
		(*dest)[1] = (((*src)[1] >> lbytes) | ((*src)[2] << rbytes));
		*src += TWO_UNROLL;
		*dest += TWO_UNROLL;
	}
	chunk_len = len / UL_SIZE;
	len %= UL_SIZE;
	while (chunk_len--)
	{
		(*dest)++[0] = (((*src)[0] >> lbytes) | ((*src)[1] << rbytes));
		(*src)++;
	}
	(*src)++;
	return (len);
}

static size_t	aligned_copy(t_ulong **dest, t_ulong **src, size_t len)
{
	size_t	chunk_len;

	chunk_len = len / (UL_SIZE * FOUR_UNROLL);
	if (chunk_len > 0)
	{
		loop_unroll(dest, src, chunk_len, FOUR_UNROLL);
		len %= (UL_SIZE * FOUR_UNROLL);
	}
	chunk_len = len / (UL_SIZE * TWO_UNROLL);
	if (chunk_len > 0)
	{
		loop_unroll(dest, src, chunk_len, TWO_UNROLL);
		len %= (UL_SIZE * TWO_UNROLL);
	}
	chunk_len = len / UL_SIZE;
	len %= UL_SIZE;
	while (chunk_len--)
		(*dest)++[0] = (*src)++[0];
	return (len);
}

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	t_uchar	*d;
	t_uchar	*s;
	size_t	misalign;

	if (!dest && !src)
		return (NULL);
	d = (t_uchar *)dest;
	s = (t_uchar *)src;
	if (len >= UL_SIZE * TWO_UNROLL && UL_SIZE != 1)
	{
		misalign = check_align(&d, &s, &len);
		if (misalign)
		{
			len = misalign_copy((t_ulong **)&d, (t_ulong **)&s, len, misalign);
			s -= (UL_SIZE - misalign);
		}
		else
			len = aligned_copy((t_ulong **)&d, (t_ulong **)&s, len);
	}
	while (len--)
		*d++ = *s++;
	return (dest);
}
