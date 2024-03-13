/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compass.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 13:27:51 by marvin            #+#    #+#             */
/*   Updated: 2024/01/15 13:27:51 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPASS_H
# define COMPASS_H

# include "render_linux.h"
# include "vector.h"
# include "drawing_algos.h"
# include "pixel_point.h"

# include <math.h>

# define MY_PI 3.14159265f

/*
 diagonal of a 90º triangle with sides 1 by 1
 by pitagoras 1^2 + 1^2 = diag^2 so diag = sqrt(2)
 div by 2 heps in getting sine and cosine at +45/-45/+135/-135 angles all
based on one single sin/cos calculation
used on defining character movement
*/
# define SQRT_OF_TWO_OVER_TWO 0.7071067f

//easier and more symetrical if letter height/width is an odd number
# define LETTER_HEIGHT 9
# define LETTER_WIDTH 5

# define CCL_MAX_RAD 300
# define CCL_MIN_RAD 50

# define SQR_MAX_HEIGHT 100
# define SQR_MIN_HEIGHT 5

typedef struct s_compass	t_compass;
typedef struct s_circle		t_circle;
typedef struct s_north		t_north;
typedef struct s_south		t_south;
typedef struct s_east		t_east;
typedef struct s_west		t_west;

/*
The compass will have a centre marker
			-> where player will be placed
			-> letter rotation using this centre
			-> circles drawn around this centre

fdf: map is static and angles are all recalculated from base map
same here: using templates for letters and squares 
with starting points
starting square is centreed at 0,0, with 
hashtable built around that point
any square to be rendered will simply be a copy of the template 
(with hashtable, after rotations)
square rotates against its own centre 
(vs letters that rotate against the compass centre)
and every point will be translated according to 
the square placement vs this centre

starting letters will be centreed around (0,0) +/- their 
offset on the compass (0,0)
then they are displaced to their positions (individual offsets)
and finally they are rotated against the centre of the compass
less calculations as their place in the circle will be already 
correct by rotating against the compass centre
compass has a starting angle, letters' angle will be define as 
a function of this one

the angles between the compass and the letters is 
determined by trigonometrics:

			north = compass
				cos (a)
				sin (a)
			east:
				cos (a + PI/2) = - sin (a);
				sin (a + PI / 2) = cos (a);
			south:
				cos (a + PI) = -cos (a);
				sin (a + PI) = -sin (a);
			west:
				cos (a - PI /2) = -sin (a);
				sin (a - PI /2) = cos (a);

east and west are the same (symetrical nature), 
but their place vs the centre of the compass is different
and that will lead them to rotate in diffent directions
*/

enum e_sqr
{
	SQR_BOT_LEFT,
	SQR_TOP_LEFT,
	SQR_TOP_RIGHT,
	SQR_BOT_RIGHT,
	SQR_SIZE,
};

enum e_min_max
{
	MM_MIN_X,
	MM_MIN_Y,
	MM_MAX_X,
	MM_MAX_Y,
	MM_SIZE,
};

typedef struct s_mm_pair
{
	int	min;
	int	max;
}	t_mm_pair;

typedef struct s_square
{
	t_pixel		centre;
	t_pixel		edges[SQR_SIZE];
	int			min_max[MM_SIZE];
	int			height;
	int			color;
	int			biggest_z;
	int			real_z;
}	t_square;

typedef struct s_render_sqr
{
	int			x;
	int			y;
	t_square	sqr;
	t_hori_line	line;
	int			c_min_max[MM_SIZE];
	int			start;
	int			end;
	int			adj_x;
}	t_render_sqr;

enum e_east
{
	E_BOT_LEFT,
	E_BOT_RIGHT,
	E_TOP_LEFT,
	E_TOP_RIGHT,
	E_MID_LEFT,
	E_MID_RIGHT,
	E_SIZE,
};

enum e_north
{
	N_BOT_LEFT,
	N_BOT_RIGHT,
	N_TOP_LEFT,
	N_TOP_RIGHT,
	N_SIZE,
};

enum e_south
{
	S_BOT_LEFT,
	S_BOT_RIGHT,
	S_TOP_LEFT,
	S_TOP_RIGHT,
	S_MID_LEFT,
	S_MID_RIGHT,
	S_SIZE,
};

enum e_west
{
	W_TOP_LEFT,
	W_MB_LEFT,
	W_TOP_MID,
	W_MB_RIGHT,
	W_TOP_RIGHT,
	W_SIZE,
};

enum e_csouth
{
	CS_BOT_LEFT,
	CS_BOT_MID,
	CS_MMB,
	CS_MMT,
	CS_TOP_MID,
	CS_TOP_RIGHT,
	CS_SIZE,
};

struct s_circle
{
	t_pixel		centre;
	int			radius;
	int			color;
	int			min_max[MM_SIZE];
};

typedef struct s_render_circ
{
	t_pixel		centre;
	t_compass	*comp;
	int			radius;
	int			rad_sqr;
	int			quarter;
	float		error;
	int			color;
	bool		with_line;
	int			c_min_max[MM_SIZE];
	t_hori_line	draw;
}	t_render_circ;

typedef struct s_comp_blur
{
	float	kernel[31];
	int		save_pixels[31];
	int		kernel_size;
	int		max_kernel;
	int		sigma;
	int		*hori_blur;
	int		*verti_blur;
	int		blur_height;
	int		centre;
	int		rad_diff;
	int		img_x;
	int		img_y;
}	t_comp_blur;

//main compass structure
struct s_compass
{
	t_pixel			centre;
	int				radius;
	int				color;
	float			angle;
	float			cos_rad;
	float			sin_rad;
	int				inner_c_rad;
	int				letter_height;
	int				letter_width;
	int				letter_radius;
	int				letter_color;
	int				sqr_color;
	int				sqr_height;
	int				player_rad;
	int				player_colour;
	t_circle		inner;
	t_square		sqr;
	t_mm_pair		*circle_x_lim;
	t_mm_pair		*sqr_x_lim;
	t_pixel			map_centre;
	bool			blur_on;
	t_comp_blur		blur;

	t_pixel			north[N_SIZE];
	t_pixel			south[S_SIZE];
	t_pixel			south_circle[S_SIZE];
	t_pixel			east[E_SIZE];
	t_pixel			west[W_SIZE];
};

//letter_north.c
void	init_template_north(t_compass *comp);
void	render_north_letter(t_win *win, t_compass *comp);

//letter_south.c
void	init_template_south(t_compass *comp);
void	render_south_letter(t_win *win, t_compass *comp);

//letter_east.c
void	init_template_east(t_compass *comp);
void	render_east_letter(t_win *win, t_compass *comp);

//letter_west.c
void	init_template_west(t_compass *comp);
void	render_west_letter(t_win *win, t_compass *comp);

//letter_south_circle.c
void	init_template_south_circle(t_compass *comp);
void	render_south_letter_circle(t_win *win, t_compass *comp);

//win_square.c
int		init_template_square(t_compass *comp);
void	compass_square_xlim_rotate(t_compass *comp, t_square *sqr);

//translate_rotate.c
void	translate_point(t_pixel	*point, int dx, int dy);
void	backward_rotate_point(t_pixel *point, t_pixel centre, \
		float cos, float sin);
void	rotate_point(t_pixel *point, t_pixel centre, float cos, float sin);

//compass_setup.c
int		compass_setup(t_compass *comp);
void	translate_compass(t_compass *comp, int dx, int dy);
void	render_compass(t_win *win, t_compass *comp);
void	free_compass(t_compass *comp);

//render_inner_circle.c
int		init_inner_circle(t_compass *comp);
void	render_inner_circle(t_win *win, t_compass *comp);

//render_inner_square.c
void	render_square_vs_circle(t_win *win, t_compass *comp, t_pixel centre);

//render_outter_circle.c
void	render_empty_circle_with_aa(t_win *win, t_pixel centre, \
		int radius, int color);
void	render_full_circle_with_aa(t_win *win, t_pixel centre, \
		int radius, int color);
void	draw_ring_to_inner_circle(t_win *win, t_compass *comp);
void	blur_compass(t_win *win, t_compass *comp);
void	blur_compass_hori_verti(t_win *win, t_compass *comp);

#endif
