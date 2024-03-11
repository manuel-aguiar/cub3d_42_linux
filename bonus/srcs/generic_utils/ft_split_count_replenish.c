/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_count_replenish.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 13:09:56 by marvin            #+#    #+#             */
/*   Updated: 2024/01/12 13:09:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_sep(char c, char *sepset)
{
	int	i;

	i = 0;
	while (sepset[i])
	{
		if (c == sepset[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	wordnum(t_cchar *str, char *sepset)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	if (str[i] && !is_sep(str[i], sepset))
		count++;
	while (str[i] && !is_sep(str[i], sepset))
		i++;
	while (str[i])
	{
		if (!is_sep(str[i], sepset) && is_sep(str[i - 1], sepset))
			count++;
		i++;
	}
	return (count);
}

static char	*lenword(t_cchar *str, char *sepset, size_t *wordlen)
{
	size_t	i;

	while (*str && is_sep(*str, sepset))
		str++;
	i = 0;
	while (str[i] && !is_sep(str[i], sepset))
		i++;
	*wordlen = i;
	return ((char *)str);
}

static char	*copyword_replenish(char *dest, t_cchar *src, \
			t_cchar *og, size_t wordlen)
{
	ft_memmove(dest, og, wordlen);
	dest[wordlen] = '\0';
	src += sizeof(*src) * wordlen;
	return ((char *)src);
}

char	**ft_split_count_replenish(t_cchar *s, t_cchar *og, \
		char *sepset, int *place_count)
{
	size_t	wordlen;
	int		i;
	char	**split;
	char	*save;

	if (!s || !og)
		return (NULL);
	save = (char *)s;
	*place_count = wordnum(s, sepset);
	split = malloc(sizeof(*split) * (*place_count + 1));
	if (!split)
		return (perror_msg_ptr("malloc", NULL));
	i = 0;
	while (i < *place_count)
	{
		s = lenword(s, sepset, &wordlen);
		split[i] = malloc(sizeof(*split[i]) * (wordlen + 1));
		if (!split[i])
			return (perror_msg_ptr("malloc", \
			ft_free_sizemat_null(&split, i, &free)));
		s = copyword_replenish(split[i], s, &og[s - save], wordlen);
		i++;
	}
	split[i] = NULL;
	return (split);
}
