/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:37:46 by marvin            #+#    #+#             */
/*   Updated: 2024/01/22 10:37:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static inline bool	char_is_player(char c)
{
	if (c == MAP_NORTH \
	|| c == MAP_SOUTH \
	|| c == MAP_EAST \
	|| c == MAP_WEST)
		return (true);
	return (false);
}

static int	validate_map_chars(t_parsing *parsing)
{
	int		i;
	int		len;
	bool	is_player;

	len = parsing->map_height * parsing->map_width;
	i = 0;
	while (i < len)
	{
		if (!char_in_charset(parsing->map[i], VALID_MAP_CHARS))
			return (error_msg_int("cub3d: invalid map characters\n", \
			STDERR_FILENO, 0));
		is_player = char_is_player(parsing->map[i]);
		if (parsing->found_player && is_player)
			return (error_msg_int("cub3d: multiple player starting points\n", \
			STDERR_FILENO, 0));
		if (is_player)
			parsing->found_player = is_player;
		i++;
	}
	if (!parsing->found_player)
		return (error_msg_int("cub3d: no player starting point\n", \
			STDERR_FILENO, 0));
	return (1);
}

static int	dump_parsing_to_map(t_map *map, t_parsing *parsing)
{
	int	i;

	*map = (t_map){};
	map->map = parsing->map;
	map->height = parsing->map_height;
	map->width = parsing->map_width;
	i = 0;
	while (i < NUM_TEX)
	{
		map->tex_data[i] = parsing->tex_data[i];
		i++;
	}
	map->len = map->width * map->height;
	map->hit = ft_calloc(map->len, sizeof(*map->hit));
	if (!map->hit)
		return (perror_msg_int("malloc", 0));
	map->doors = ft_calloc(map->len, sizeof(*map->doors));
	if (!map->doors)
		return (perror_msg_int("malloc", 0));
	return (1);
}

int	map_parsing(t_map *map, char *av_file)
{
	t_parsing	parsing;

	parsing = (t_parsing){};
	parsing.file = av_file;
	if (!file_to_list(&parsing) \
	|| !separate_textures(&parsing) \
	|| !get_map_dimensions(&parsing) \
	|| !list_to_map(&parsing) \
	|| !validate_map_chars(&parsing) \
	|| !flood_count_island(&parsing) \
	|| !analise_textures(&parsing) \
	|| !dump_parsing_to_map(map, &parsing))
	{
		vdmlist_destroy(&parsing.list, free_gnl_len);
		return (0);
	}
	vdmlist_destroy(&parsing.list, free_gnl_len);
	return (1);
}
