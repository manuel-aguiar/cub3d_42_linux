/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bullet_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 13:06:56 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:40:27 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	enemy_take_damage(t_game *game, t_sprite *sprite)
{
	t_enemy	*enemy;

	if (sprite->type != ENEMY)
		return ;
	enemy = (t_enemy *)sprite->data;
	enemy->health -= game->player.attack;
	if (enemy->health <= 0)
	{
		sprite->status = GONE;
		game->enemy_count--;
	}
}

int	target_was_hit_on_z(t_game *game, t_bullet_colli *colli, \
		t_sprite *sprite, t_sprite *target)
{
	float	z;

	z = vec3d_get_z_from_xy(colli->bullet->posi, colli->bullet->dir, \
		colli->collision[0]);
	if (z >= target->cur_z && z <= target->cur_z + target->height)
	{
		sprite->status = GONE;
		if (target->type == ENEMY)
			enemy_take_damage(game, target);
		return (1);
	}
	z = vec3d_get_z_from_xy(colli->bullet->posi, colli->bullet->dir, \
		colli->collision[1]);
	if (z >= target->cur_z && z <= target->cur_z + target->height)
	{
		sprite->status = GONE;
		if (target->type == ENEMY)
			enemy_take_damage(game, target);
		return (1);
	}
	return (0);
}

void	set_hitbox(t_sprite *target, t_vec2d box[2])
{
	t_door	*door;

	if (target->type == ENEMY)
	{
		box[0] = (t_vec2d){target->posi.x - target->unit_size, target->posi.y \
			- target->unit_size};
		box[1] = (t_vec2d){target->posi.x + target->unit_size, target->posi.y \
			+ target->unit_size};
	}
	if (target->type == DOOR)
	{
		door = (t_door *)target->data;
		if (door->orient == NS)
		{
			box[0] = (t_vec2d){target->posi.x - 0.5f, target->posi.y - 0.05f};
			box[1] = (t_vec2d){target->posi.x + 0.5f, target->posi.y + 0.05f};
		}
		else
		{
			box[0] = (t_vec2d){target->posi.x - 0.05f, target->posi.y - 0.5f};
			box[1] = (t_vec2d){target->posi.x + 0.05f, target->posi.y + 0.5f};
		}
	}
}

int	friendly_bullet(t_game *game, t_bullet_colli *colli, t_sprite *sprite)
{
	t_sprite		*target;
	t_hitnode		*node;

	node = game->map.hit[colli->map_index].head;
	while (node)
	{
		target = node->sprite;
		set_hitbox(target, colli->box);
		if (liang_barsky_hit(colli->box, colli->check, colli->collision) \
		&& target_was_hit_on_z(game, colli, sprite, target))
			return (1);
		node = node->next;
	}
	return (0);
}
