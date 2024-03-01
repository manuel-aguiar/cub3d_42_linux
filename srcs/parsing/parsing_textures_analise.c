/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:59:39 by marvin            #+#    #+#             */
/*   Updated: 2024/01/22 10:59:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	color_atoi(char *str, int *place_res)
{
	int	res;

	if (!ft_isdigit(*str))
		return (0);
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str++ - '0');
		if (res > MAX_COLOR)
			return (0);
	}
	if (*str)
		return (0);
	*place_res = res;
	return (1);
}

static int	extract_color(t_tex	*tex)
{
	char	**split;
	int		count;
	int		r;
	int		g;
	int		b;

	split = ft_split_count(tex->path, ",", &count);
	if (!split)
		return (perror_msg_int("malloc", 0));
	if (count != 3 \
	|| !color_atoi(split[0], &r) \
	|| !color_atoi(split[1], &g) \
	|| !color_atoi(split[2], &b))
	{
		ft_free_charmat_null(&split, free);
		return (0);
	}
	tex->color = rgba(r, g, b, START_ALPHA);
	ft_free_set_null(&tex->path);
	ft_free_charmat_null(&split, free);
	return (1);
}

int	analise_textures(t_parsing *parsing)
{
	int	i;

	i = 0;
	while (i < NUM_TEX)
	{
		if (!ft_strncmp("./", parsing->tex_data[i].path, 2))
			parsing->tex_data[i].type = PATH_TEX;
		else
		{
			parsing->tex_data[i].type = COLOR_TEX;
			if (!extract_color(&parsing->tex_data[i]))
				return (0);
		}
		i++;
	}
	return (1);
}
