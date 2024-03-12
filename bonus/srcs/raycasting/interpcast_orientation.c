/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpcast_orientation.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/04 13:13:43 by marvin            #+#    #+#             */
/*   Updated: 2024/03/12 19:18:34 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

static inline void	door_orientation(t_game *game, t_sprite *sprite, \
	t_interp_cast *cast)
{
	if (cast->door->orient == NS)
	{
		cast->inverted = false;
		cast->start.point = (t_vec2d){sprite->posi.x - 0.5f, sprite->posi.y};
		cast->end.point = (t_vec2d){sprite->posi.x + 0.5f, sprite->posi.y};
	}
	else
	{
		cast->inverted = true;
		cast->start.point = (t_vec2d){sprite->posi.x, sprite->posi.y - 0.5f};
		cast->end.point = (t_vec2d){sprite->posi.x, sprite->posi.y + 0.5f};
	}
	if ((cast->door->orient == NS \
	&& game->player.map_posi.y > cast->start.point.y) \
	|| (cast->door->orient == WE \
	&& game->player.map_posi.x > cast->start.point.x))
	{
		vec2d_swap(&cast->start.point, &cast->end.point);
		cast->inverted = !cast->inverted;
	}
}

static inline void	bullet_orientation(t_sprite *sprite, \
	t_interp_cast *cast)
{
	bool	ns;

	cast->inverted = false;
	ns = (ft_fabs(cast->bullet->hole.y - (int)cast->bullet->hole.y) < 0.0001f);
	if (ns)
	{
		cast->start.point = (t_vec2d){cast->bullet->hole.x - sprite->unit_size, \
			cast->bullet->hole.y};
		cast->end.point = (t_vec2d){cast->bullet->hole.x + sprite->unit_size, \
			cast->bullet->hole.y};
	}
	else
	{
		cast->start.point = (t_vec2d){cast->bullet->hole.x, \
			cast->bullet->hole.y - sprite->unit_size};
		cast->end.point = (t_vec2d){cast->bullet->hole.x, cast->bullet->hole.y \
			+ sprite->unit_size};
	}
}

void	setup_orientation(t_game *game, t_sprite *sprite, t_interp_cast *cast)
{
	if (sprite->type == DOOR)
	{
		cast->door = (t_door *)sprite->data;
		cast->tex = &game->tex[DOOR_TEX];
		door_orientation(game, sprite, cast);
	}
	else if (sprite->type == BULLET)
	{
		cast->bullet = (t_bullet *)sprite->data;
		cast->tex = &game->tex[WALL_BULLET_TEX];
		bullet_orientation(sprite, cast);
	}
}
