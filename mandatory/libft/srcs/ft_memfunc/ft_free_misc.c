/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_misc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 16:13:03 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 16:13:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memfunc.h"

void	*ft_free_set_null(void *ptr)
{
	t_uchar	**to_free;

	to_free = (unsigned char **)ptr;
	if (*to_free)
		free(*to_free);
	*to_free = NULL;
	return (NULL);
}

void	*ft_free_charmat(void *table, void (*del)(void *))
{
	int		i;
	char	**split;

	if (!table)
		return (NULL);
	split = *(char ***)table;
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		del(split[i]);
		split[i] = NULL;
		i++;
	}
	return (ft_free_set_null(&split));
}

void	*ft_free_charmat_null(void *table, void (*del)(void *))
{
	int		i;
	char	**split;

	if (!table)
		return (NULL);
	split = *(char ***)table;
	if (!split)
		return (NULL);
	i = 0;
	while (split[i])
	{
		del(split[i]);
		split[i] = NULL;
		i++;
	}
	return (ft_free_set_null(table));
}

void	*ft_free_sizemat(void *table, size_t size, void (*del)(void *))
{
	size_t		i;
	char		**split;

	if (!table)
		return (NULL);
	split = *(char ***)table;
	if (!split)
		return (NULL);
	i = 0;
	while (i < size)
	{
		del(split[i]);
		split[i] = NULL;
		i++;
	}
	return (ft_free_set_null(&split));
}

void	*ft_free_sizemat_null(void *table, size_t size, void (*del)(void *))
{
	size_t		i;
	char		**split;

	if (!table)
		return (NULL);
	split = *(char ***)table;
	if (!split)
		return (NULL);
	i = 0;
	while (i < size)
	{
		del(split[i]);
		split[i] = NULL;
		i++;
	}
	return (ft_free_set_null(table));
}
