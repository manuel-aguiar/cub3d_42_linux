/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_bullet.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:14:44 by marvin            #+#    #+#             */
/*   Updated: 2024/02/29 15:14:44 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	enemy_take_damage(t_game *game, t_sprite *sprite)
{
	t_enemy	*enemy;

	if (sprite->type != ENEMY)
		return ;
	printf("hit!! ");
	enemy = (t_enemy *)sprite->data;
	enemy->health -= game->player.attack;
	if (enemy->health <= 0)
	{
		sprite->status = GONE;
		game->enemy_count--;
		printf("enemy down!!\n");
	}
	else
		printf("\n");
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

void	setup_bullet_hit(t_game *game, t_bullet_colli *colli, t_sprite *sprite)
{
	colli->bullet = (t_bullet *)sprite->data;
	colli->map_index = (int)sprite->posi.x + (int)sprite->posi.y \
		* game->map.width;
	colli->check[0] = (t_vec2d){sprite->posi.x, sprite->posi.y};
	sprite->posi.x += colli->bullet->dir.x * colli->bullet->move_sense \
		* game->player.clock->elapsed;
	sprite->posi.y += colli->bullet->dir.y * colli->bullet->move_sense \
		* game->player.clock->elapsed;
	sprite->cur_z += colli->bullet->dir.z * colli->bullet->move_sense \
		* game->player.clock->elapsed;
	colli->bullet->posi = (t_vec3d){sprite->posi.x, sprite->posi.y, \
		sprite->cur_z};
	colli->check[1] = (t_vec2d){sprite->posi.x, sprite->posi.y};
}

void	update_bullet(t_game *game, t_sprite *sprite)
{
	t_sprite		*target;
	t_hitnode		*node;
	t_bullet_colli	colli;
	t_vec3d			sub;
	float			dot;

	setup_bullet_hit(game, &colli, sprite);
	node = game->map.hit[colli.map_index].head;
	while (node)
	{
		target = node->sprite;
		set_hitbox(target, colli.box);
		if (liang_barsky_hit(colli.box, colli.check, colli.collision) \
		&& target_was_hit_on_z(game, &colli, sprite, target))
			return ;
		node = node->next;
	}
	sub = vec3d_sub(colli.bullet->posi, colli.bullet->hole);
	dot = sub.x * colli.bullet->dir.x + sub.y * colli.bullet->dir.y \
		+ sub.z * colli.bullet->dir.z;
	if (dot <= 0)
	{
		if (colli.bullet->hole.z < 0 || colli.bullet->hole.z > 1)
			sprite->status = GONE;
		else
			sprite->status = ON_WALL;
	}

}
