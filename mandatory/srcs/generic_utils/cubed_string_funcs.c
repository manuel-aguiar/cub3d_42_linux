/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_in_charset.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 20:04:19 by marvin            #+#    #+#             */
/*   Updated: 2024/02/22 20:04:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "generic_utils.h"

int	char_in_charset(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_only_spaces(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}

int	count_char(char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	return (count);
}
