/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_hitmap_clean.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:36:34 by codespace         #+#    #+#             */
/*   Updated: 2024/03/11 13:42:21 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static void	clean_hitnodes_and_map(t_game *game, t_sprite *sprite)
{
	int	map_index;

	map_index = (int)(sprite->posi.x - sprite->unit_size) \
	+ (int)(sprite->posi.y - sprite->unit_size) * game->map.width;
	if (game->map.hit[map_index].len != 0)
		ft_memset(&game->map.hit[map_index], 0, sizeof(t_hitlist));
	map_index = (int)(sprite->posi.x + sprite->unit_size) \
	+ (int)(sprite->posi.y + sprite->unit_size) * game->map.width;
	if (game->map.hit[map_index].len != 0)
		ft_memset(&game->map.hit[map_index], 0, sizeof(t_hitlist));
	map_index = (int)(sprite->posi.x - sprite->unit_size) \
	+ (int)(sprite->posi.y + sprite->unit_size) * game->map.width;
	if (game->map.hit[map_index].len != 0)
		ft_memset(&game->map.hit[map_index], 0, sizeof(t_hitlist));
	map_index = (int)(sprite->posi.x + sprite->unit_size) \
	+ (int)(sprite->posi.y - sprite->unit_size) * game->map.width;
	if (game->map.hit[map_index].len != 0)
		ft_memset(&game->map.hit[map_index], 0, sizeof(t_hitlist));
	ft_memset(&sprite->my_hit[0], 0, sizeof(sprite->my_hit));
	sprite->my_hit[0].sprite = sprite;
	sprite->my_hit[1].sprite = sprite;
	sprite->my_hit[2].sprite = sprite;
	sprite->my_hit[3].sprite = sprite;
}

static void	clean_hitnodes_and_map_door(t_game *game, t_sprite *sprite)
{
	t_door	*door;

	door = (t_door *)sprite->data;
	if (game->map.hit[door->map_index].len != 0)
		ft_memset(&game->map.hit[door->map_index], 0, sizeof(t_hitlist));
	sprite->my_hit[0].sprite = sprite;
	sprite->my_hit[0].prev = NULL;
	sprite->my_hit[0].next = NULL;
}

void	clean_hitmap(t_game *game)
{
	int			i;
	t_sprite	*sprite;

	i = 0;
	while (i < game->sprite_count)
	{
		sprite = game->sorted[i];
		if (sprite->type == ENEMY)
			clean_hitnodes_and_map(game, sprite);
		else if (sprite->type == DOOR)
			clean_hitnodes_and_map_door(game, sprite);
		i++;
	}
}
