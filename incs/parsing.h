/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 10:35:48 by marvin            #+#    #+#             */
/*   Updated: 2024/01/22 10:35:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H

# define PARSING_H

# include <unistd.h>
# include <fcntl.h>

# include "libft.h"
# include "render_linux.h"
# include "vector.h"
# include "pixel_point.h"
# include "hit_detection.h"

# define TOTAL_TEXTURES 6

# define VALID_MAP_CHARS "01NSWEMAZXDT "

# define VALID_DIR_CHARS "NSWE"

# define MAP_MEDI 'M'
# define MAP_AMMO 'A'
# define MAP_ENEMY 'Z'
# define MAP_EXIT 'X'
# define MAP_DOOR 'D'
# define MAP_EMPTY ' '

# define MAP_FLOOR '0'
# define MAP_WALL '1'
# define MAP_NORTH 'N'
# define MAP_SOUTH 'S'
# define MAP_EAST 'E'
# define MAP_WEST 'W'


# define FLOOD_CHAR '.'

# define START_ALPHA 255
# define MAX_COLOR 255
# define MIN_COLOR 0

typedef struct s_sprite t_sprite;

typedef	enum
{
	NO_TEX,
	SO_TEX,
	WE_TEX,
	EA_TEX,
	F_TEX,
	C_TEX,
	MEDI_TEX,
	AMMO_TEX,
	ENEMY_TEX,
	BULLET_TEX,
	GUN_TEX,
	DOOR_TEX,
	NUM_TEX,
}	e_textures;

enum e_tex_type
{
	PATH_TEX,
	COLOR_TEX,
};

typedef struct s_tex
{
	int		type;
	char	*path;
	int		color;
}	t_tex;

typedef struct s_parsing
{
	t_vdmlist	*list;
	char		*file;
	int			file_len;
	int			fd;
	char		*gnl;
	int			nbr_tex;
	int			index_tex;
	char		**split;
	int			split_count;	
	t_tex		tex_data[NUM_TEX];
	char		*map;
	int			map_width;
	int			map_height;
	bool		found_player;
	char		*map_copy;
	bool		ff_found;
	int			ff_count;
}	t_parsing;

typedef struct s_map
{
	char		*map;
	t_hitlist	*hit;
	t_sprite	**doors;
	int			width;
	int			height;
	int			len;
	t_tex		tex_data[NUM_TEX];
}	t_map;


//parsing_main.c
int		map_parsing(t_map *map, char *av_file);


//parsing_print_utils.c
void	print_tex_data(t_parsing *parsing);
void	gnl_len_print_line(void	*str);
void	print_map(t_map *map);
void	print_flood_fill(char *map, int height, int width);

//map_funcs.c
void	free_map(t_map *map);
int		map_row(t_map *map, int index);
int		map_col(t_map *map, int index);

//map_dimensions.c
int		get_map_dimensions(t_parsing *parsing);

//map_flood_count.c
int		flood_count_island(t_parsing *parse);

//parsing_textures_get.c
int		separate_textures(t_parsing *parsing);

//parsing_textures_analise.c
int		analise_textures(t_parsing *parsing);

//parsing_file_to_list.c
int 	file_to_list(t_parsing *parsing);
int		list_to_map(t_parsing *parsing);

#endif