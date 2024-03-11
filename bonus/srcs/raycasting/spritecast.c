/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spritecast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:47:02 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:47:02 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

void	setup_common_spritecast(t_game *game, t_sp_cast *cast);
void	setup_this_spritecast(t_game *game, t_sp_cast *cast, int i);

void	sprite_vertical_line(t_game *game, t_sp_cast *cast, int x)
{
	int	y;

	cast->tex_exact_y = cast->tex_step_y * (0 - cast->bot_pix_y) \
		* (0 > cast->bot_pix_y);
	y = ft_max(0, cast->bot_pix_y);
	cast->top_pix_y = ft_min(cast->win_h - 1, cast->top_pix_y);
	while (y < cast->top_pix_y)
	{
		cast->tex_pix_y = (int)(cast->tex_exact_y);
		cast->tex_exact_y += cast->tex_step_y;
		cast->color = tex_get_pixel(&game->win, cast->tex, cast->tex_pix_x \
			* cast->tex->width + cast->tex_pix_y);
		if (cast->color != 0)
		{
			cast->color = add_shade(cast->color, cast->shade_wgt);
			game->win.set_pixel(&game->win, x, y, cast->color);
		}
		y++;
	}
}

void	cast_this_sprite(t_game *game, t_sp_cast *cast)
{
	int	x;

	if (cast->trans.y > 0)
	{
		cast->tex_exact_x = cast->tex_step_x * (0 - cast->left_pix_x) \
			* (0 > cast->left_pix_x);
		x = ft_max(0, cast->left_pix_x);
		cast->right_pix_x = ft_min(cast->win_w - 1, cast->right_pix_x);
		while (x < cast->right_pix_x)
		{
			cast->tex_pix_x = (int)(cast->tex_exact_x);
			cast->tex_exact_x += cast->tex_step_x;
			if (cast->sprite->inverted)
				cast->tex_pix_x = cast->tex->height - cast->tex_pix_x - 1;
			if (x > 0 && x < cast->win_w && cast->trans.y \
				< game->hori_rays[x].wall_dist)
				sprite_vertical_line(game, cast, x);
			x++;
		}
	}
}

void	sprite_cast(t_game *game)
{
	t_sp_cast	cast;
	int			i;

	setup_common_spritecast(game, &cast);
	i = 0;
	while (i < game->sprite_count)
	{
		if (game->sorted[i]->type == DOOR \
		|| (game->sorted[i]->type == BULLET \
			&& game->sorted[i]->status == ON_WALL))
			interpcast(game, game->sorted[i]);
		else if (game->sorted[i]->status != GONE)
		{
			setup_this_spritecast(game, &cast, i);
			cast_this_sprite(game, &cast);
		}
		i++;
	}
}
