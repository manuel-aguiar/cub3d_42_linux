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

void	swap_verti_coords(t_mlx_img	*tex)
{
	int	row;
	int	col;
	int	temp;
	int	first_index;
	int	second_index;

	row = 0;
	while (row < tex->height)
	{
		col = 0;
		while (col < tex->width / 2)
		{
			first_index = (row * tex->width + col) * tex->bpp / 8;
			second_index = ((row + 1) * tex->width - col - 1) * tex->bpp / 8;
			temp = *(int *)&tex->pixels[first_index];
			*(int *)&tex->pixels[first_index] \
				= *(int *)&tex->pixels[second_index];
			*(int *)&tex->pixels[second_index] = temp;
			col++;
		}
		row++;
	}
}

int	mlx_image_transpose(t_game *game, t_tex_data *data, int i, t_mlx_img *tex)
{
	t_mlx_img	new;
	int			row;
	int			col;
	int			src_index;
	int			dest_index;

	new.img = mlx_xpm_file_to_image(game->win.mlx, \
		data->path, &new.width, &new.height);
	if (!new.img)
		return (error_msg_int("cub3d: mlx xpm to image failed\n", STDERR_FILENO, 0));
	new.pixels = mlx_get_data_addr(new.img, &new.bpp, &new.line_len, &new.endian);
	row = -1;
	while (++row < tex->height)
	{
		col = -1;
		while(++col < tex->width)
		{
			src_index = (col + row * tex->width) * tex->bpp / 8;
			dest_index = (row + col * tex->height) * tex->bpp / 8;
			*(int *)(&new.pixels[dest_index]) = *(int *)(&tex->pixels[src_index]);
		}
	}
	mlx_destroy_image(game->win.mlx, tex->img);
	int_swap(&new.width, &new.height);
	swap_verti_coords(&new);
	game->tex[i] = new;
	return (1);
}

int		mlx_load_from_xpm(t_game *game, t_tex_data *data, int i)
{
	t_mlx_img	*tex;

	tex = &game->tex[i];
	tex->img = mlx_xpm_file_to_image(game->win.mlx, \
		data->path, &tex->width, &tex->height);
	if (!tex->img)
		return (error_msg_int("cub3d: mlx xpm to image failed\n", STDERR_FILENO, 0));
	tex->pixels = mlx_get_data_addr(tex->img, &tex->bpp, &tex->line_len, &tex->endian);
	if (i != F_TEX && i != C_TEX && i != GUN_TEX && !mlx_image_transpose(game, data, i, tex))
		return (0);
	ft_free_set_null(&data->path);
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
		{
			ft_free_set_null(&data->path);
			return (0);
		}
			
		i++;
	}
	return (1);
}
