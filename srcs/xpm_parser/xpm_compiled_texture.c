/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xpm_compiled_texture.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 11:32:34 by marvin            #+#    #+#             */
/*   Updated: 2024/02/05 11:32:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "xpm_parser.h"

void	print_tex(t_xpm_tex *tex)
{
	printf("tex: width %d, height %d\n", tex->width, tex->height);
	int i;

	i = 0;
	while (i < tex->width * tex->height)
	{
		if (i % tex->width == 0)
			printf("\n");
		printf("index %d = %d    ", i, tex->pixels[i]);
		i++;
	}
	printf("\n");
}

void	print_xpm_pair(t_xpm_pair *id_color, int color_count)
{
	printf("id color:\n");
	int i;
	
	i = 0;
	while (i < color_count)
	{
		printf("id : [%s], color [%d]\n", id_color[i].id, id_color[i].color);
		i++;
	}
}

static void	*free_xpm_tex(t_xpm_tex **tex)
{
	if (((*tex)->pixels))
		free((*tex)->pixels);
	ft_free_set_null(tex);
	return (NULL);
}

static void	*free_xpm_pair(t_xpm_pair **id_color, int color_count)
{
	int			i;
	t_xpm_pair *og;

	og = *id_color;
	i = 0;
	while (i < color_count)
	{
		if (og[i].id)
			free(og[i].id);
		i++;
	}
	ft_free_set_null(id_color);
	return (NULL);
}

static int		xpm_pair_has_dups(t_xpm_pair *id_color, int color_count, int id_len)
{
	int i;
	int	j;

	i = 0;
	while (i < color_count)
	{
		j = i + 1;
		while (j < color_count)
		{
			if (!ft_strncmp(id_color[i].id, id_color[j].id, id_len))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int		color_at_target(t_xpm_pair *id_color, int color_count, char *target, int id_len)
{
	int	i;

	i = 0;
	while (i < color_count)
	{
		if (!ft_strncmp(target, id_color[i].id, id_len))
			return (id_color[i].color);
		i++;
	}
	return (-1);
}

static int	rgb_to_rgba(int rgb)
{
	return ((rgb << 8) | 0xFF);
}

void	tex_int_swap(int *a, int *b)
{
	int temp;

	temp = *a;
	*a = *b;
	*b = temp;
	//*a = *a ^ *b;
	//*b = *a ^ *b;
	//*a = *a ^ *b;
}

void	transposed_swap_coords(t_xpm_parser *parse)
{
	int	row;
	int	col;

	row = 0;
	while (row < parse->tex->height)
	{
		col = 0;
		while (col < parse->tex->width / 2)
		{
			tex_int_swap(&parse->tex->pixels[row * parse->tex->width + col],
			&parse->tex->pixels[(row + 1) * parse->tex->width - col - 1]);
			col++;
		}
		row++;
	}
}

void	*xpm_set_pixel_transposed(t_xpm_parser *parse)
{
	int swap;
	int offset = 1 + parse->color_count;
	int row = 0;
	int col;
	int index;
	//row + col * tex->height
	offset = 1 + parse->color_count;
	row = 0;
	while (row < parse->tex->height)
	{
		if (!parse->xpm[row + offset] || ! parse->xpm[row + offset][0])
		{
			free_xpm_pair(&parse->id_color, parse->color_count);
			return (free_xpm_tex(&parse->tex));
		}
		col = 0;
		while (col < parse->tex->width)
		{
			
			if (!parse->xpm[row + offset][col * parse->id_len])
			{
				free_xpm_pair(&parse->id_color, parse->color_count);
				return (free_xpm_tex(&parse->tex));
			}
			index = row + col * parse->tex->height;
			//if (index % parse->tex->width < parse->tex->width / 2)
			//	index += parse->tex->width / 2;
			//else if (index % parse->tex->width > parse->tex->width / 2)
			//	index -= parse->tex->width / 2;
			//index = index - index % parse->tex->width + (parse->tex->width - index % parse->tex->width);
			parse->tex->pixels[index] = color_at_target(parse->id_color, parse->color_count, &parse->xpm[row + offset][col * parse->id_len], parse->id_len);
			//printf("at index %d, color is %d\n", index, tex->pixels[index]);
			if (parse->tex->pixels[index] == -1)
			{
				free_xpm_pair(&parse->id_color, parse->color_count);
				return (free_xpm_tex(&parse->tex));
			}
			//printf(" rgb %d ", tex->pixels[index]);
			parse->tex->pixels[index] = rgb_to_rgba(parse->tex->pixels[index]);
			//printf(" rgb   A   %d ", tex->pixels[index]);
			col++;
		}
		row++;
	}
	
	swap = parse->tex->width;
	parse->tex->width = parse->tex->height;
	parse->tex->height = swap;
	transposed_swap_coords(parse);
	return ((void *)1);
}

void	*xpm_set_pixel_regular(t_xpm_parser *parse)
{
	int	i;
	int	j;
	int index;

	index = 0;
	i = 1 + parse->color_count;

	while (i < 1 + parse->color_count + parse->tex->height)
	{
		if (!parse->xpm[i] || ! parse->xpm[i][0])
		{
			free_xpm_pair(&parse->id_color, parse->color_count);
			return (free_xpm_tex(&parse->tex));
		}
		j = 0;
		while (j < parse->tex->width * parse->id_len)
		{
			if (!parse->xpm[i][j])
			{
				free_xpm_pair(&parse->id_color, parse->color_count);
				return (free_xpm_tex(&parse->tex));
			}
			parse->tex->pixels[index] = color_at_target(parse->id_color, parse->color_count, &parse->xpm[i][j], parse->id_len);
			//printf("at index %d, color is %d\n", index, tex->pixels[index]);
			if (parse->tex->pixels[index] == -1)
			{
				free_xpm_pair(&parse->id_color, parse->color_count);
				return (free_xpm_tex(&parse->tex));
			}
			//printf(" rgb %d ", tex->pixels[index]);
			parse->tex->pixels[index] = rgb_to_rgba(parse->tex->pixels[index]);
			//printf(" rgb   A   %d ", tex->pixels[index]);
			index++;
			j += parse->id_len;
		}
		i++;
	}
	return ((void *)1);
}

void	*xpm_set_id_color(t_xpm_parser *parse)
{
	int i;
	int	j;

	i = 0;
	while (i < parse->color_count)
	{
		if (!parse->xpm[1 + i])
			return (free_xpm_tex(&parse->tex));		
		parse->id_color[i].id = malloc(sizeof(char) * (parse->id_len + 1));
		if (!parse->id_color[i].id)
		{
			free_xpm_pair(&parse->id_color, parse->color_count);
			return (free_xpm_tex(&parse->tex));
		}
		j = -1;
		while (++j < parse->id_len)
			parse->id_color[i].id[j] = parse->xpm[1 + i][j];
		parse->id_color[i].id[j] = '\0';
		while (parse->xpm[1 + i][j] != '#')
			j++;
		if (!parse->xpm[1 + i][j])
		{
			free_xpm_pair(&parse->id_color, parse->color_count);
			return (free_xpm_tex(&parse->tex));
		}
		parse->id_color[i].color = ft_atoi_base(&parse->xpm[1 + i][j + 1], "0123456789ABCDEF");
		i++;
	}
	if (xpm_pair_has_dups(parse->id_color, parse->color_count, parse->id_len))
	{
		free_xpm_pair(&parse->id_color, parse->color_count);
		return (free_xpm_tex(&parse->tex));
	}
	return ((void *)1);
}

t_xpm_tex	*xpm_to_tex(char *xpm[], e_tex_type tex_type)
{
	t_xpm_parser	parse;

	if (!xpm || ! xpm[0])
		return (NULL);
	parse.type = tex_type;
	parse.xpm = xpm;
	parse.tex = malloc(sizeof(*parse.tex));
	if (!parse.tex)
		return (NULL);
	*parse.tex = (t_xpm_tex){};
	parse.tex->type = tex_type;
	parse.split = ft_split_count(parse.xpm[0], " ", &parse.s_count);
	if (!parse.split)
		return (free_xpm_tex(&parse.tex));
		
	if (parse.s_count != 4)
	{
		ft_free_charmat_null(&parse.split, free);
		return (free_xpm_tex(&parse.tex));
	}
	parse.tex->width = ft_atoi(parse.split[0]);
	parse.tex->height = ft_atoi(parse.split[1]);
	parse.color_count = ft_atoi(parse.split[2]);
	parse.id_len = ft_atoi(parse.split[3]);
	ft_free_charmat_null(&parse.split, free);
	if (parse.tex->width <= 0 || parse.tex->height <= 0 || parse.color_count <= 0 || parse.id_len <= 0)
		return (free_xpm_tex(&parse.tex));
	parse.tex->pixels = malloc(sizeof(*parse.tex->pixels) * parse.tex->width * parse.tex->height);
	if (!parse.tex->pixels)
		return (free_xpm_tex(&parse.tex));
	parse.id_color = ft_calloc(parse.color_count, sizeof(*parse.id_color));
	if (!parse.id_color)
		return (free_xpm_tex(&parse.tex));
	if(!xpm_set_id_color(&parse))
		return (NULL);
	if (tex_type == TEX_TRANSPOSED && !xpm_set_pixel_transposed(&parse))
		return (NULL);
	if (tex_type == TEX_REGULAR && !xpm_set_pixel_regular(&parse))
		return (NULL);
	free_xpm_pair(&parse.id_color, parse.color_count);
	return (parse.tex);
}

int	xpm_tex_copy_transpose(t_xpm_tex *tex)
{
	int	*new_pixels;
	int	swap;
	int	row;
	int	col;

	new_pixels = malloc(sizeof(*new_pixels) * tex->width * tex->height);
	if (!new_pixels)
		return (perror_msg_int("malloc", 0));
	row = 0;
	while (row < tex->height)
	{
		col = 0;
		while( col < tex->width)
		{
			new_pixels[row + col * tex->height] = tex->pixels[col + row * tex->width];
			col++;
		}
		row++;
	}
	free(tex->pixels);
	tex->pixels = new_pixels;
	swap = tex->width;
	tex->width = tex->height;
	tex->height = swap;
	return (1);
}