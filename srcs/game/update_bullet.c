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
	t_enemy *enemy;

	if (sprite->type != ENEMY)
		return ;
	enemy = (t_enemy *)sprite->data;
	enemy->health -= game->player.attack;
	if (enemy->health <= 0)
		sprite->status = GONE;
}





void		update_bullet(t_game *game, t_sprite *sprite)
{
	t_bullet	*bullet;
	t_door		*door;
	t_sprite 	*target;
	t_vec2d		map_square;
	t_hitnode	*node;
	t_vec2d		check[2];
	t_vec2d		box[2];
	t_vec2d		collision[2];
	float		z;
	int			index;

	bullet = (t_bullet *)sprite->data;
	map_square = (t_vec2d){(int)sprite->posi.x, (int)sprite->posi.y};
	index = map_square.x + map_square.y * game->map.width;
	node = game->map.hit[index].head;
	check[0] = (t_vec2d){sprite->posi.x, sprite->posi.y};
	sprite->posi.x += bullet->dir.x * bullet->move_sense * game->player.clock->elapsed;
	sprite->posi.y += bullet->dir.y * bullet->move_sense * game->player.clock->elapsed;
	sprite->cur_z += bullet->dir.z * bullet->move_sense * game->player.clock->elapsed;
	bullet->posi = (t_vec3d){sprite->posi.x, sprite->posi.y, sprite->cur_z};
	check[1] = (t_vec2d){sprite->posi.x, sprite->posi.y};
	while (node)
	{
		target = node->sprite;
		if (target->type == ENEMY)
		{
			box[0] = (t_vec2d){target->posi.x - target->unit_size, target->posi.y - target->unit_size};
			box[1] = (t_vec2d){target->posi.x + target->unit_size, target->posi.y + target->unit_size};
		}
		if (target->type == DOOR)
		{
			door = (t_door *)target->data;
			if (door->orient == NS)
			{
				box[0] = (t_vec2d){target->posi.x - 0.5f, target->posi.y - 0.01f};
				box[1] = (t_vec2d){target->posi.x + 0.5f, target->posi.y + 0.01f};
			}
			else
			{
				box[0] = (t_vec2d){target->posi.x - 0.01f, target->posi.y - 0.5f};
				box[1] = (t_vec2d){target->posi.x + 0.01f, target->posi.y + 0.5f};
			}
		}
		if (liang_barsky_hit(box, check, collision))
		{
			z = vec3d_get_z_from_xy(bullet->posi, bullet->dir, collision[0]);
			if (z >= target->cur_z && z <= target->cur_z + target->height)
			{
				sprite->status = GONE;
				if (target->type == ENEMY)
					enemy_take_damage(game, target);
				printf("hit!!\n");
				return ;
			}
			z = vec3d_get_z_from_xy(bullet->posi, bullet->dir, collision[1]);
			if (z >= target->cur_z && z <= target->cur_z + target->height)
			{
				sprite->status = GONE;
				if (target->type == ENEMY)
					enemy_take_damage(game, target);
				printf("hit!!\n");
				return ;
			}
			else
				printf("missed on z\n");
		}
		else
			printf("missed on liang\n");
		node = node->next;
	}

	t_vec3d sub = vec3d_sub(bullet->posi, bullet->hole);
	float dot = sub.x * bullet->dir.x + sub.y * bullet->dir.y + sub.z * bullet->dir.z;

	if (dot <= 0)
		sprite->status = GONE;
}
