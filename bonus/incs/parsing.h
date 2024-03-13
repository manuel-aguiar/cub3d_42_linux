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

# define VALID_MAP_CHARS "01NSWEMAXYZD "
# define VALID_DIR_CHARS "NSWE"
# define SPRITE_CHARS "MAXYZD"

//letra M = 77
# define MAP_MEDI 77
//letra A = 65
# define MAP_AMMO 65
//letra X = 88
# define MAP_X_ENEMY 88
//letra Y = 89
# define MAP_Y_ENEMY 89
//letra Z = 90
# define MAP_Z_ENEMY 90
//letra D = 68
# define MAP_DOOR 68
//space = 32
# define MAP_EMPTY 32

//char '0' = 48
# define MAP_FLOOR 48
//char '1' = 49
# define MAP_WALL 49
//letra N = 78
# define MAP_NORTH 78
//letra S = 83
# define MAP_SOUTH 83
//letra E = 69
# define MAP_EAST 69
//letra W = 87
# define MAP_WEST 87
//char '.' = 46
# define FLOOD_CHAR 46

# define START_ALPHA 255
# define MAX_COLOR 255
# define MIN_COLOR 0

typedef struct s_sprite	t_sprite;

//enumerator for textures, NUM_TEX at the end
//serves as a counter for total structs
typedef enum e_textures
{
	NO_TEX,
	SO_TEX,
	WE_TEX,
	EA_TEX,
	F_TEX,
	C_TEX,
	MEDI_TEX,
	AMMO_TEX,
	X_ENEMY_TEX,
	Y_ENEMY_TEX,
	Z_ENEMY_TEX,
	MY_BULLET_TEX,
	EN_BULLET_TEX,
	WALL_BULLET_TEX,
	GUN_TEX,
	DOOR_TEX,
	NUM_TEX,
}	t_textures;

typedef enum e_tex_type
{
	PATH_TEX,
	COLOR_TEX,
}	t_tex_type;

typedef struct s_tex
{
	t_tex_type		type;
	char			*path;
	int				color;
}	t_tex_data;

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
	t_tex_data	tex_data[NUM_TEX];
	char		*map;
	int			map_width;
	int			map_height;
	int			map_len;
	bool		found_player;
	char		*map_copy;
	bool		ff_found;
	int			ff_count;
}	t_parsing;

typedef struct s_map
{
	char			*map;
	t_hitlist		*hit;
	t_sprite		**doors;
	int				width;
	int				height;
	int				len;
	t_tex_data		tex_data[NUM_TEX];
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
int		file_to_list(t_parsing *parsing);
int		list_to_map(t_parsing *parsing);
void	destroy_parsing(t_parsing *parsing);

#endif
