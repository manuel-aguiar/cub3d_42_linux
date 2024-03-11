/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 14:39:02 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 14:39:02 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*
removed loop unroll from misaligned copy to fit norminette size :) :
chunk_len = (len / (UL_SIZE * TWO_UNROLL));
	len %= (UL_SIZE * TWO_UNROLL);
	while (chunk_len--)
	{
		*src -= TWO_UNROLL;
		*dest -= TWO_UNROLL;
		(*dest)[1] = (((*src)[1] >> lbytes) | ((*src)[2] << rbytes));
		(*dest)[0] = (((*src)[0] >> lbytes) | ((*src)[1] << rbytes));
	}
*/
#include "ft_memfunc.h"

static size_t	rev_check_align(t_uchar **dest, t_uchar **src, size_t *len)
{
	t_ulong	check;

	while (((t_ulong)(*dest) & (UL_ALIGN)) != 0)
	{
		*(*dest)-- = *(*src)--;
		(*len)--;
	}
	**dest = **src;
	(*len)--;
	check = ((t_ulong)(*src) & (UL_ALIGN));
	if (check != 0)
	{
		*src -= (check);
		return ((check));
	}
	return (0);
}

static void	rev_loop_unroll(t_ulong **dest, t_ulong **src, size_t chunk,
		size_t roll)
{
	if (roll == FOUR_UNROLL)
	{
		while (chunk--)
		{
			*dest -= FOUR_UNROLL;
			*src -= FOUR_UNROLL;
			(*dest)[3] = (*src)[3];
			(*dest)[2] = (*src)[2];
			(*dest)[1] = (*src)[1];
			(*dest)[0] = (*src)[0];
		}
	}
	else
	{
		while (chunk--)
		{
			*dest -= TWO_UNROLL;
			*src -= TWO_UNROLL;
			(*dest)[1] = (*src)[1];
			(*dest)[0] = (*src)[0];
		}
	}
}

static size_t	rev_misalign_copy(t_ulong **dest, t_ulong **src, size_t len,
		size_t bytedif)
{
	size_t	chunk_len;
	t_uchar	lbytes;
	t_uchar	rbytes;

	lbytes = (bytedif * CHAR_BIT);
	rbytes = (UL_SIZE * CHAR_BIT) - lbytes;
	chunk_len = len / UL_SIZE;
	len %= UL_SIZE;
	(*src)--;
	(*dest)--;
	while (chunk_len--)
	{
		(*dest)--[0] = (((*src)[0] >> lbytes) | ((*src)[1] << rbytes));
		(*src)--;
	}
	*(t_uchar **)dest += UL_ALIGN;
	*(t_uchar **)src += UL_ALIGN;
	return (len);
}

static size_t	rev_aligned_copy(t_ulong **dest, t_ulong **src, size_t len)
{
	size_t	chunk_len;

	chunk_len = len / (UL_SIZE * FOUR_UNROLL);
	if (chunk_len > 0)
	{
		rev_loop_unroll(dest, src, chunk_len, FOUR_UNROLL);
		len %= (UL_SIZE * FOUR_UNROLL);
	}
	chunk_len = len / (UL_SIZE * TWO_UNROLL);
	if (chunk_len > 0)
	{
		rev_loop_unroll(dest, src, chunk_len, TWO_UNROLL);
		len %= (UL_SIZE * TWO_UNROLL);
	}
	chunk_len = len / UL_SIZE;
	len %= UL_SIZE;
	(*src)--;
	(*dest)--;
	while (chunk_len--)
		(*dest)--[0] = (*src)--[0];
	*(t_uchar **)dest += UL_ALIGN;
	*(t_uchar **)src += UL_ALIGN;
	return (len);
}

void	*ft_memmove(void *dest, const void *src, size_t len)
{
	t_uchar	*d;
	t_uchar	*s;
	size_t	misalign;

	if (!dest && !src)
		return (NULL);
	if ((t_uchar *)src > (t_uchar *)dest)
		return (ft_memcpy(dest, src, len));
	d = (t_uchar *)dest + len - 1;
	s = (t_uchar *)src + len - 1;
	if (len >= UL_SIZE * TWO_UNROLL && UL_SIZE != 1)
	{
		misalign = rev_check_align(&d, &s, &len);
		if (misalign)
		{
			len = rev_misalign_copy((t_ulong **)&d, (t_ulong **)&s,
					len, misalign);
			s += misalign;
		}
		else
			len = rev_aligned_copy((t_ulong **)&d, (t_ulong **)&s, len);
	}
	while (len--)
		*d-- = *s--;
	return (dest);
}
