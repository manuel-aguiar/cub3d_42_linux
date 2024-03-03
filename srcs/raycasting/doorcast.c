/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doorcast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 21:52:50 by marvin            #+#    #+#             */
/*   Updated: 2024/02/12 21:52:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "game.h"

typedef struct s_door_cast
{
	int		start_x;
	int		end_x;
	int		width;
	int		min_start_y;
	int		max_start_y;
	int 	min_end_y;
	int 	max_end_y;
	float	delta_min_y;
	float	delta_max_y;
	float	exact_min_y;
	float	exact_max_y;
	int		this_min_y;
	int		this_max_y;
}	t_door_cast;

void	setup_doorcast(t_game *game, t_door *door, t_door_cast *cast)
{
	(void)game;
	cast->min_start_y = door->start.min_y;
	cast->max_start_y = door->start.max_y;
	cast->min_end_y = door->end.min_y;
	cast->max_end_y = door->end.max_y;
	cast->start_x = door->start_x;
	cast->end_x = door->end_x;
	cast->width = cast->end_x - cast->start_x;
	cast->delta_min_y = (float)(cast->min_end_y - cast->min_start_y) / (float)cast->width;
	cast->delta_max_y = (float)(cast->max_end_y - cast->max_start_y) / (float)cast->width;
	cast->exact_min_y = cast->min_start_y;
	cast->exact_max_y = cast->max_start_y;
}


void	doorcast(t_game *game, t_sprite *sprite)
{
	int w = game->win.width;
	int h = game->win.height;
	t_door		*door;
	t_xpm_tex 	*tex;
	t_vec2d	door_start;
	t_vec2d	door_end;
	t_vec2d	rel_start;
	t_vec2d	rel_end;
	t_vec2d	transform_start;
	t_vec2d	transform_end;
	t_vec2d	dir = vec2d_multi(game->player.dir_vec, game->player.cur_dir_len);

	bool inverted;
	door = (t_door *)sprite->data;
	if (door->orient == NS)
	{
		inverted = false;
		door_start = (t_vec2d){sprite->posi.x - 0.5f, sprite->posi.y};
		door_end = (t_vec2d){sprite->posi.x + 0.5f, sprite->posi.y};
	}
	else
	{
		inverted = true;
		door_start = (t_vec2d){sprite->posi.x, sprite->posi.y - 0.5f};
		door_end = (t_vec2d){sprite->posi.x, sprite->posi.y + 0.5f};
	}
	if ((door->orient == NS && game->player.map_posi.y > door_start.y) \
	|| (door->orient == WE && game->player.map_posi.x > door_start.x))
	{
		vec2d_swap(&door_start, &door_end);
		inverted = !inverted;
	}
	//print_sorted_sprites(game);
	//exit(0);
	

	float invDet = 1.0 / (game->player.plane.x * dir.y - game->player.plane.y * dir.x);

		rel_start = vec2d_sub(door_start, game->player.map_posi);
		transform_start.x = (dir.y * rel_start.x - dir.x * rel_start.y);
		transform_start.y = (-game->player.plane.y * rel_start.x + game->player.plane.x * rel_start.y);
		transform_start = vec2d_multi(transform_start, invDet);

		rel_end = vec2d_sub(door_end, game->player.map_posi);
		transform_end.x = (dir.y * rel_end.x - dir.x * rel_end.y);
		transform_end.y = (-game->player.plane.y * rel_end.x + game->player.plane.x * rel_end.y);
		transform_end = vec2d_multi(transform_end, invDet);

		if (transform_end.y < 0 && transform_start.y < 0)
			return ;

		int screen_start_x = (int)((w / 2) * (1 + transform_start.x / transform_start.y));
		if (transform_start.y < 0)
			screen_start_x = (int)((w / 2) * (1 - transform_start.x / transform_start.y));
		int height_start = abs((int)(h * 1.0f / (transform_start.y))); 

		int screen_end_x = (int)((w / 2) * (1 + transform_end.x / transform_end.y));
		if (transform_end.y < 0)
			screen_end_x = (int)((w / 2) * (1 - transform_end.x / transform_end.y));
		int height_end = abs((int)(h * 1.0f / (transform_end.y))); 
		
		
		
		//calculate lowest and highest pixel to fill in current stripe
		int min_startY = -height_start / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2) / transform_start.y);
		//if(min_startY < 0) min_startY = 0;
		int max_startY = height_start / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2) / transform_start.y);
		//if(max_startY >= h) max_startY = h - 1;

		int min_endY = -height_end / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2) / transform_end.y);
		//if(min_endY < 0) min_endY = 0;
		int max_endY = height_end / 2 + h / 2 + game->player.pitch - (int)(((game->player.cur_z + game->player.jump_z_mod + game->player.walk_z_mod) * h - h / 2) / transform_end.y);
		//if(max_endY >= h) max_endY = h - 1;

		if (screen_end_x < screen_start_x)
		{
			int_swap(&screen_start_x, &screen_end_x);
			int_swap(&height_start, &height_end);
			int_swap(&min_startY, &min_endY);
			int_swap(&max_startY, &max_endY);
			vec2d_swap(&transform_start, &transform_end);
		}
		//screen_end_x = int_clamp(screen_end_x, (int)(-w * 0.5f), (int)(w * 1.5f));
		//screen_start_x = int_clamp(screen_start_x, (int)(-w * 0.5f), (int)(w * 1.5f));
		tex = game->tex[DOOR_TEX];
		//calculate width of the sprite
		int drawStartX = screen_start_x;
		int drawEndX = screen_end_x;
		
		/*
		//draw left
		int lineHeight = max_startY - min_startY;
		double step_y = 1.0f * tex->width / lineHeight;
		double tex_position_y = 0;
		int texX = 0;
		
		if (drawStartX > 0 && drawStartX < w)
		{
			int y = min_startY;
			while (y++ < int_clamp(min_startY, 0, h - 1))
				tex_position_y += step_y;
			while (y < int_clamp(max_startY, 0, h - 1))
			{
				float shade = ft_fabs(transform_start.y / game->max_vis_dist * game->player.cur_dir_len / game->player.base_dir_len);
				int texY = (int)tex_position_y;
				tex_position_y += step_y;

				int color = tex->pixels[texX * tex->width + (tex->width - texY - 1)];
				color = add_shade(color, shade);
				game->win.set_pixel(&game->win, drawStartX, y, color);
				y++;
			}
		}
		*/

		/*
		y = int_clamp(min_endY, 0, h - 1);

		if (drawEndX > 0 && drawEndX < w)
		{
			while (y < int_clamp(max_endY, 0, h - 1))
			{
				float shade = ft_fabs(transform_end.y / game->max_vis_dist * game->player.cur_dir_len / game->player.base_dir_len);
				int color = rgba(255,0,0,255);
				color = add_shade(color, shade);
				game->win.set_pixel(&game->win, drawEndX, y, color);
				y++;
			}
		}
		*/
		
		
		int x_width = drawEndX - drawStartX;
		
		float shade_start = ft_fabs(transform_start.y / game->max_vis_dist * game->player.cur_dir_len / game->player.base_dir_len);
		float shade_end = ft_fabs(transform_end.y / game->max_vis_dist * game->player.cur_dir_len / game->player.base_dir_len);

		float delta_min_y = (float)(min_endY - min_startY) / (float)x_width;
		float delta_max_y = (float)(max_endY - max_startY) / (float)x_width;

		//printf("delta min %.3f, delta max %.3f min max start %d %d, min max end %d %d\n", delta_min_y, delta_max_y, min_startY, max_startY, min_endY, max_endY);

		int save_startX = drawStartX;

		(void)shade_start;
		(void)shade_end;
		(void)save_startX;

		int x = drawStartX;
		float min_y = min_startY;
		float max_y = max_startY;
		//x_width = int_clamp(x_width, -w, w);
		double step_x = 1.0f * tex->height / x_width;
		double tex_position_x = 0;
		while (x++ < 0)
		{
			tex_position_x += step_x;
			min_y += delta_min_y;
			max_y += delta_max_y;
		}
			
		while (x < drawEndX)
		{
			int texX;
			if (inverted)
				texX = (tex->width - (int)tex_position_x - 1);
			else
				texX = (int)tex_position_x;
			tex_position_x += step_x;

			
			float perc = (float)(x - save_startX) / (float)x_width;
			int start_y = (int)min_y;
			int	end_y = (int)max_y;
			int lineHeight = end_y - start_y;
			if(x > 0 && x < w && lineHeight >= game->hori_rays[x].line_h)
			//if(x > 0 && x < w && distance > 0 && distance < game->hori_rays[drawStartX].wall_dist)
			{
				
				double step_y = 1.0f * tex->width / lineHeight;
				double tex_position_y = 0;
				

				while (start_y++ < 0)
					tex_position_y += step_y;
				while (start_y < int_clamp(end_y, 0, h - 1))
				{
					float shade = shade_start * (1 - perc) + shade_end * perc;
					int texY = (int)tex_position_y;
					tex_position_y += step_y;

					int color = tex->pixels[texX * tex->width + texY];
					if (color != 0)
					{
						color = add_shade(color, shade);
						game->win.set_pixel(&game->win, x, start_y, color);
					}

					start_y++;
				}
			}
			min_y += delta_min_y;
			max_y += delta_max_y;
			x++;
		}
}