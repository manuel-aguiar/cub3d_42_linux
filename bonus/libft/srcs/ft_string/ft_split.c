/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:31:26 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:31:26 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"

static size_t	wordnum(t_cchar *str, char sep)
{
	size_t	count;
	int		i;

	i = 0;
	count = 0;
	if (str[i] && str[i] != sep)
		count++;
	while (str[i] && str[i] != sep)
		i++;
	while (str[i])
	{
		if (str[i] != sep && str[i - 1] == sep)
			count++;
		i++;
	}
	return (count);
}

static char	*lenword(t_cchar *str, char sep, size_t *wordlen)
{
	size_t	i;

	while (*str && *str == sep)
		str++;
	i = 0;
	while (str[i] && str[i] != sep)
		i++;
	*wordlen = i;
	return ((char *)str);
}

static char	*copyword(char *dest, t_cchar *src, size_t wordlen)
{
	ft_memmove(dest, src, wordlen);
	dest[wordlen] = '\0';
	src += sizeof(*src) * wordlen;
	return ((char *)src);
}

void	ft_free_split(void *table)
{
	ft_free_charmat(table, &free);
}

char	**ft_split(t_cchar *s, char c)
{
	size_t	numwords;
	size_t	wordlen;
	size_t	i;
	char	**split;

	if (!s)
		return (NULL);
	numwords = wordnum(s, c);
	split = malloc(sizeof(*split) * (numwords + 1));
	if (!split)
		return (perror_msg_ptr("malloc", NULL));
	i = 0;
	while (i < numwords)
	{
		s = lenword(s, c, &wordlen);
		split[i] = malloc(sizeof(*split[i]) * (wordlen + 1));
		if (!split[i])
			return (perror_msg_ptr("malloc", \
			ft_free_sizemat_null(&split, i, &free)));
		s = copyword(split[i], s, wordlen);
		i++;
	}
	split[i] = NULL;
	return (split);
}

/*
#include <stdio.h>
int main (void)
{
	char str[] = "teste";

	char **ptr = ft_split(" bruh",' ');

	int i = 0;
	if (ptr)
	{
		while (ptr[i])
			printf("%s\n", ptr[i++]);
	}
}*/
