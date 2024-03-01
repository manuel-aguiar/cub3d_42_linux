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
	t_enemy		*enemy;
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
		box[0] = (t_vec2d){target->posi.x - target->unit_size, target->posi.y - target->unit_size};
		box[1] = (t_vec2d){target->posi.x + target->unit_size, target->posi.y + target->unit_size};
		enemy = (t_enemy *)target->data;
		if (liang_barsky_hit(box, check, collision))
		{
			z = vec3d_get_z_from_xy(bullet->posi, bullet->dir, collision[0]);
			if (z >= target->cur_z && z <= target->cur_z + target->height)
			{
				sprite->status = GONE;
				enemy_take_damage(game, target);
				printf("hit!!\n");
				return ;
			}
			z = vec3d_get_z_from_xy(bullet->posi, bullet->dir, collision[1]);
			if (z >= target->cur_z && z <= target->cur_z + target->height)
			{
				sprite->status = GONE;
				enemy->health -= bullet->attack_val;
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