/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_setup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:46:13 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:46:13 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	fill_sorted_pointers(t_game *game);
int		fill_with_bullets(t_game *game);
int		place_bullet(t_game *game, int place);

int	extract_sprites(t_game *game, t_map *map)
{
	int	i;
	int	cur;

	i = 0;
	cur = 0;
	while (cur < game->sprite_count)
	{
		while (!char_in_charset(map->map[i], SPRITE_CHARS))
			i++;
		if ((map->map[i] == MAP_MEDI && !extract_medi(game, map, cur, i)) \
		|| (map->map[i] == MAP_AMMO && !extract_ammo(game, map, cur, i)) \
		|| (map->map[i] == MAP_DOOR && !extract_door(game, map, cur, i)) \
		|| (map->map[i] == MAP_X_ENEMY && !extract_x_enemy(game, map, cur, i)) \
		|| (map->map[i] == MAP_Y_ENEMY && !extract_y_enemy(game, map, cur, i)) \
		|| (map->map[i] == MAP_Z_ENEMY && !extract_z_enemy(game, map, cur, i)))
			return (0);
		i++;
		cur++;
	}
	return (1);
}

void	setup_common_sprite(t_sprite *array, int count)
{
	int			i;
	t_sprite	*sprite;

	i = 0;
	while (i < count)
	{
		sprite = &array[i];
		sprite->my_hit[0].sprite = sprite;
		sprite->my_hit[1].sprite = sprite;
		sprite->my_hit[2].sprite = sprite;
		sprite->my_hit[3].sprite = sprite;
		sprite->status = NOT_VIS;
		sprite->inverted = false;
		sprite->dist = FLT_MAX;
		i++;
	}
}

int	sprites_count_and_malloc(t_map *map, t_sprite **place_array, \
							int *count, int max_bullets)
{
	int			i;

	i = 0;
	*count = 0;
	while (i < map->len)
	{
		if (char_in_charset(map->map[i], SPRITE_CHARS))
			(*count)++;
		i++;
	}
	*place_array = malloc(sizeof(**place_array) * (*count + max_bullets));
	if (!*place_array)
		return (perror_msg_int("malloc", 0));
	setup_common_sprite(*place_array, (*count + max_bullets));
	return (1);
}

int	setup_sprites(t_game *game)
{
	t_sprite	*array;
	t_map		*map;
	int			count;

	map = &game->map;
	if (!sprites_count_and_malloc(map, &array, &count, game->max_bullets))
		return (0);
	game->sprites = array;
	game->sprite_count = count;
	if (!extract_sprites(game, map))
		return (0);
	if (!fill_with_bullets(game))
		return (0);
	game->sprite_count += game->max_bullets;
	game->sorted = malloc(sizeof(*game->sorted) * game->sprite_count);
	if (!game->sorted)
		return (perror_msg_int("malloc", 0));
	fill_sorted_pointers(game);
	return (1);
}
