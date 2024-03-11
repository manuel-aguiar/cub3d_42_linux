/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_extract_sort_bullets.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 15:24:26 by codespace         #+#    #+#             */
/*   Updated: 2024/03/11 13:42:12 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int	place_bullet(t_game *game, int place)
{
	t_bullet	*data;
	t_sprite	*sprite;

	sprite = &game->sprites[place];
	data = malloc(sizeof(*data));
	if (!data)
		return (perror_msg_int("malloc", 0));
	ft_memcpy(data, &game->template_bullet, sizeof(*data));
	sprite->data = data;
	sprite->type = BULLET;
	sprite->status = GONE;
	sprite->cur_z = data->base_z;
	sprite->height = data->height;
	sprite->unit_size = data->unit_size;
	sprite->tex = MY_BULLET_TEX;
	return (1);
}

int	fill_with_bullets(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->max_bullets)
	{
		if (!place_bullet(game, game->sprite_count + i))
			return (0);
		i++;
	}
	return (1);
}

void	fill_sorted_pointers(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->sprite_count)
	{
		game->sorted[i] = &game->sprites[i];
		i++;
	}
}
