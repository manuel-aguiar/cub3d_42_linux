/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_extract_doors.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:18:13 by codespace         #+#    #+#             */
/*   Updated: 2024/03/11 13:42:10 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	check_door_orient(t_map *map, t_door *door, \
	t_sprite *sprite, int map_index)
{
	map->doors[map_index] = sprite;
	if (map->map[map_index + 1] == MAP_WALL \
	&& map->map[map_index - 1] == MAP_WALL \
	&& map->map[map_index + map->width] != MAP_WALL \
	&& map->map[map_index - map->width] != MAP_WALL)
		door->orient = NS;
	else if (map->map[map_index + 1] != MAP_WALL \
	&& map->map[map_index - 1] != MAP_WALL \
	&& map->map[map_index + map->width] == MAP_WALL \
	&& map->map[map_index - map->width] == MAP_WALL)
		door->orient = WE;
	else
		return (error_msg_int("cub3d: doors are missplaced\n", \
			STDERR_FILENO, 0));
	door->base_position = sprite->posi;
	return (1);
}

int	extract_door(t_game *game, t_map *map, int place, int map_index)
{
	t_door		*data;
	t_sprite	*sprite;

	sprite = &game->sprites[place];
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_door, sizeof(*data));
	data->map_index = map_index;
	sprite->data = data;
	sprite->type = DOOR;
	sprite->posi.x = (float)map_col(map, map_index) + 0.5f;
	sprite->posi.y = (float)map_row(map, map_index) + 0.5f;
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->unit_size = 0.5f;
	sprite->width = 0;
	sprite->tex = DOOR_TEX;
	if (!check_door_orient(map, data, sprite, map_index))
		return (0);
	return (1);
}
