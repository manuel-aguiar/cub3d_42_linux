/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_player_collisions.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/24 17:06:07 by marvin            #+#    #+#             */
/*   Updated: 2024/01/24 17:06:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

/*
https://github.com/OneLoneCoder/Javidx9/blob/master/PixelGameEngine/SmallerProjects/OneLoneCoder_PGE_CircleVsRect.cpp
*/



void	handle_collisions(t_game *game, t_vec2d *posi, t_vec2d potencial, float unit_size)
{
	t_map		*map;
	int			fixed_x;
	int			fixed_y;

	//float		float_x;
	//float		float_y;

	
	map = &game->map;
	fixed_x = (int)posi->x;
	fixed_y = (int)posi->y;
	
	float potential_len;

	int divide_potential;

	potential_len = vec2d_len(potencial);
	divide_potential = 1 + (int)(potential_len / unit_size);

	

	t_sprite 	*sprite;
	t_door 		*door;
	
	//float_x = posi->x - fixed_x;
	//float_y = posi->y - fixed_y;

	//printf("i am at (%.3f, %.3f), my square is %c\n", posi->x, posi->y, map->map[fixed_x + fixed_y * map->width]);
	//check left
	int i;

	t_vec2d	add;
	t_vec2d player;

	
	add = vec2d_multi(potencial, (1 / (float)divide_potential));
	i = 0;
	while (i < divide_potential)
	{

		player = *posi;
		*posi = vec2d_add(*posi, add);
		if (map->map[fixed_x + fixed_y * map->width] == MAP_DOOR)
		{
			sprite = map->doors[fixed_x + fixed_y * map->width];
			door = (t_door *)sprite->data;
			if (door->state == DOOR_CLOSED)
			{
				if (door->orient == NS)
				{
					if (player.y < sprite->posi.y)
						posi->y = ft_fmin(posi->y, sprite->posi.y - (unit_size));
					else
						posi->y = ft_fmax(posi->y, sprite->posi.y + (unit_size));
				}
				else
				{
					if (player.x < sprite->posi.x)
						posi->x = ft_fmin(posi->x, sprite->posi.x - (unit_size));
					else
						posi->x = ft_fmax(posi->x, sprite->posi.x + (unit_size));					
				}
			}
		}




		
		if (map->map[(fixed_x - 1) + fixed_y * map->width] == MAP_WALL)
			posi->x = ft_fmax(posi->x, fixed_x + (unit_size));
		if (map->map[(fixed_x + 1) + fixed_y * map->width] == MAP_WALL)
			posi->x = ft_fmin(posi->x, fixed_x + 1 - (unit_size));
		if (map->map[fixed_x + (fixed_y + 1) * map->width] == MAP_WALL)
			posi->y = ft_fmin(posi->y, fixed_y + 1 - (unit_size));
		if (map->map[fixed_x + (fixed_y - 1) * map->width] == MAP_WALL)
			posi->y = ft_fmax(posi->y, fixed_y + (unit_size));


		t_vec2d nearest;
		t_vec2d ray_to_nearest;
		float ray_length;
		float overlap;
		

		//check topo left
		//printf("fixed x %d, fixed y %d, index top left %d\n", fixed_x, fixed_y,(fixed_x - 1) + (fixed_y + 1) * map->width);
		if (map->map[(fixed_x - 1) + (fixed_y + 1) * map->width] == MAP_WALL)
		{
			//printf("posi start (%.3f, %.3f)\n", posi->x, posi->y);
			nearest.x = ft_fmin(posi->x, (float)fixed_x);
			nearest.y = ft_fmax(posi->y, (float)(fixed_y + 1));
			ray_to_nearest = vec2d_sub(nearest,  *posi);
			ray_length = vec2d_len(ray_to_nearest);

			overlap = unit_size - ray_length;
			if (overlap > 0)
			{
				ray_to_nearest = vec2d_norm(ray_to_nearest, ray_length);
				*posi = vec2d_sub(*posi, vec2d_multi(ray_to_nearest, overlap));
			}
			//printf("posi end (%.3f, %.3f)\n", posi->x, posi->y);
		}
		//top right
		if (map->map[(fixed_x + 1) + (fixed_y + 1) * map->width] == MAP_WALL)
		{
			//printf("posi start (%.3f, %.3f)\n", posi->x, posi->y);
			nearest.x = ft_fmax(posi->x, (float)(fixed_x + 1));
			nearest.y = ft_fmax(posi->y, (float)(fixed_y + 1));
			ray_to_nearest = vec2d_sub(nearest,  *posi);
			ray_length = vec2d_len(ray_to_nearest);

			overlap = unit_size - ray_length;
			if (overlap > 0)
			{
				ray_to_nearest = vec2d_norm(ray_to_nearest, ray_length);
				*posi = vec2d_sub(*posi, vec2d_multi(ray_to_nearest, overlap));
			}
		}

		//bot left
		if (map->map[(fixed_x - 1) + (fixed_y - 1) * map->width] == MAP_WALL)
		{
			//printf("posi start (%.3f, %.3f)\n", posi->x, posi->y);
			nearest.x = ft_fmin(posi->x, (float)(fixed_x));
			nearest.y = ft_fmin(posi->y, (float)(fixed_y));
			ray_to_nearest = vec2d_sub(nearest,  *posi);
			ray_length = vec2d_len(ray_to_nearest);

			overlap = unit_size - ray_length;
			if (overlap > 0)
			{
				ray_to_nearest = vec2d_norm(ray_to_nearest, ray_length);
				*posi = vec2d_sub(*posi, vec2d_multi(ray_to_nearest, overlap));
			}
		}

		//bot right
		if (map->map[(fixed_x + 1) + (fixed_y - 1) * map->width] == MAP_WALL)
		{
			//printf("posi start (%.3f, %.3f)\n", posi->x, posi->y);
			nearest.x = ft_fmax(posi->x, (float)(fixed_x + 1));
			nearest.y = ft_fmin(posi->y, (float)(fixed_y));
			ray_to_nearest = vec2d_sub(nearest, *posi);
			ray_length = vec2d_len(ray_to_nearest);

			overlap = unit_size - ray_length;
			if (overlap > 0)
			{
				ray_to_nearest = vec2d_norm(ray_to_nearest, ray_length);
				*posi = vec2d_sub(*posi, vec2d_multi(ray_to_nearest, overlap));
			}
		}
		i++;
	}
		//*posi = vec2d_add(*posi, potencial);





	//printf("*posi (%.3f, %.3f)\n", posi->x, posi->y);


	
}

/*

	//printf("player in %d, %d\n", fixed_x, fixed_y);
	//t_vec2d nearest;
	//t_vec2d ray_to_nearest;
	//float	ray_length;
	//float	overlap;
	//int			x;
	//int			y;
	//x = -1;
	//while (x <= 1)
	//{
	//	y = -1;
	//	while (y <= 1)
	//	{
	//		//printf("checking point %d, %d\n", (fixed_x + x), (fixed_y + y));
	//		if (map->map[(fixed_x + x) + (fixed_y + y) * map->width] == '1')
	//		{
	//			//printf("posi start (%.3f, %.3f)\n", posi->x, posi->y);
	//			nearest.x = ft_fmax(fixed_x + x, ft_fmin(potencial_posi.x, fixed_x + x + 1));
//
	//			nearest.y = ft_fmax(fixed_y + y, ft_fmin(potencial_posi.y, fixed_y + y + 1));
	//			//if (y == 1 && nearest.y > fixed_y + y)
	//			//	nearest.y = fixed_y + y;
	//			ray_to_nearest = vec2d_sub(nearest, potencial_posi);
	//			ray_length = vec2d_len(ray_to_nearest);
//
	//			overlap = unit_size - ray_length;
	//			if (overlap > 0)
	//			{
	//				
	//				printf("player at %d, %d, collision registered at %d, %d\n", fixed_x, fixed_y, (fixed_x + x), (fixed_y + y));
	//				printf("player is (%.3f, %.3f), radius (%.3f), wants to be (%.3f, %.3f)\n", posi->x, posi->y, unit_size, potencial_posi.x, potencial_posi.y);
	//				printf("nearest (%.3f, %.3f), ray_to_nearest (%.3f, %.3f) ray_len (%.3f)\n", nearest.x, nearest.y, ray_to_nearest.x, ray_to_nearest.y, ray_length);
	//				
	//				potencial_posi = vec2d_sub(potencial_posi, vec2d_multi(vec2d_norm(ray_to_nearest, ray_length), overlap));
	//				printf("new player posi will be (%.3f, %.3f)\n", potencial_posi.x, potencial_posi.y);
	//			}
	//		}
	//		y++;
	//	}
	//	x++;
	//}
	
	
	*/