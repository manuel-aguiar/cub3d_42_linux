/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:15:42 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:15:42 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
first part of the algorithm is to set the word at the natural alignment of
memory onthat architecture (could be 4bytes,
ould be 8). the string being aligned is what allows to do the bit
manipulation without problems as the CPU can calculate all the math at once
without changing pages, due to the natural alignemnt. While aligning,
we need to count characters one by one.

After alignment comes the tricky part....


longword
- lomagic: if the byte in longword is zero or larger than 0x80 (max
signed char) the difference will set the most significant
bit (to the left) to 1

~longword & himagic: if there are no nulls or overflown chars,
the result equals himagic
itself (himagic is the MSB set to 1, rest 0)

final: if byte is not null,
the diffference will be zero because they will have no 1-bits
in common (& equals zero in all bits, implying a missfire).
if it is a null: first expression places a 1 in MSB,
second expression keeps the 1 in MSB
when you & both,
the result will be not 00000000 since the MSB will be for sure turned on,
like 10000000.

after seeing that one byte is null,
se still don't know which one-> loop unroll (faster?)

*/

#include "ft_string.h"

size_t	ft_strlen(t_cchar *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
#define RIGHT_BIT_ONE 0x01010101
#define LEFT_BIT_ONE 0x80808080

static void	expand_mask(t_ulong *right_one, t_ulong *left_one)
{
	*right_one = RIGHT_BIT_ONE;
	*left_one = LEFT_BIT_ONE;
	if (UL_SIZE > 4)
	{
		*right_one = ((*right_one << 16) << 16) | *right_one;
		*left_one = ((*left_one << 16) << 16) | *left_one;
	}
}

static size_t	loop_unroll(t_cchar *str, t_cchar *i, size_t size)
{
	if (i[0] == 0)
		return ((size_t)(i - str));
	if (i[1] == 0)
		return ((size_t)(i - str + 1));
	if (i[2] == 0)
		return ((size_t)(i - str + 2));
	if (i[3] == 0)
		return ((size_t)(i - str + 3));
	if (size > 4)
	{
		if (i[4] == 0)
			return ((size_t)(i - str + 4));
		if (i[5] == 0)
			return ((size_t)(i - str + 5));
		if (i[6] == 0)
			return ((size_t)(i - str + 6));
		if (i[7] == 0)
			return ((size_t)(i - str + 7));
	}
	return (0);
}

size_t	ft_strlen(t_cchar *str)
{
	t_cchar	*i;
	t_ulong	*longword_ptr;
	t_ulong	longword;
	t_ulong	left_one;
	t_ulong	right_one;

	i = str;
	while (((t_ulong)i & (UL_SIZE - 1)) != 0)
	{
		if (!*i)
			return (i - str);
		i++;
	}
	longword_ptr = (t_ulong *)i;
	expand_mask(&right_one, &left_one);
	while (1)
	{
		longword = *longword_ptr++;
		if (((longword - right_one) & ~longword & left_one) != 0)
		{
			i = (t_cchar *)(longword_ptr - 1);
			return (loop_unroll(str, i, UL_SIZE));
		}
	}
}
*/

/*

#include <stdio.h>
#include <unistd.h>


int	main(void)
{
    char str[] = "uma frase qualquer";

    printf("len of '%s' is %ld\n", str, strlenlen(str));

    write(1, "\n", 1);
    return (0);
}

*/
