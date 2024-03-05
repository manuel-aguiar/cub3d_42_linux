/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loud_textures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 11:00:29 by codespace         #+#    #+#             */
/*   Updated: 2024/03/05 11:21:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"

int		mlx_load_from_xpm(t_game *game, t_tex_data *data, int i)
{
	t_xpm_tex	*tex;

	tex = &game->tex[i];
	tex->type = i;
	tex->pixels = mlx_xpm_file_to_image(game->win.mlx, \
		data->path, &tex->width, &tex->height);
	ft_free_set_null(&data->path);
	if (!tex->pixels)
		return (0);
	return (1);
}

int		game_load_textures(t_game *game)
{
	int 		i;
	t_tex_data	*data;

	i = 0;
	while (i < NUM_TEX)
	{
		data = &game->map.tex_data[i];
		if (data->type == COLOR_TEX)
			game->colors[i] = data->color;
		else if (!mlx_load_from_xpm(game, data, i))
			return (0);
		i++;
	}
	return (1);
}
