/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_algos.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:04:59 by marvin            #+#    #+#             */
/*   Updated: 2024/01/26 19:04:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAWING_ALGOS_H

# define DRAWING_ALGOS_H

# include "libft.h"
# include "render_linux.h"
# include "vector.h"
# include "pixel_point.h"

//struct for liang barsky clipping
typedef struct s_lbclip
{
	int		p1;
	int		p2;
	int		p3;
	int		p4;
	int		q1;
	int		q2;
	int		q3;
	int		q4;
	float	posarr[5];
	float	negarr[5];
	int		posind;
	int		negind;
	float	r1;
	float	r2;
	float	r3;
	float	r4;
	int		xn1;
	int		yn1;
	int		xn2;
	int		yn2;
	float	rn1;
	float	rn2;
	t_pixel	box[2];
	t_pixel	line[2];
}	t_lbclip;

//helper struct to draw xiaolinwu lines
typedef struct s_xldata
{
	unsigned short	err_adj;
	unsigned short	err_acc;
	unsigned short	err_temp;
	short			dx;
	short			dy;
	short			save;
	short			slope;
	int				colour;
}	t_xldata;

//helper struct to draw bersenham lines
typedef struct s_bh_line
{
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	err_2;
}	t_bh_line;

//helper struct to draw horizontal lines
typedef struct s_hori_line
{
	int	min_x;
	int	max_x;
	int	y;
	int	color;
}	t_hori_line;

//helper struct to draw vertical lines
typedef struct s_verti_line
{
	int	min_y;
	int	max_y;
	int	x;
	int	color;
}	t_verti_line;

//liang barsky
int		liang_barsky_clipping(t_pixel win[2], t_pixel draw[2], t_pixel res[2]);
float	lb_maxi(float arr[], int n);
float	lb_mini(float arr[], int n);

//xiaolin_wu.c
int		xiaolinwu_line(t_win *win, t_pixel start, t_pixel end);

//drawing lines.c
void	draw_horizontal_line(t_win *win, t_hori_line *data);
void	draw_vertical_line(t_win *win, t_verti_line *data);
void	bersenham_line(t_win *win, t_pixel start, t_pixel end, int color);

#endif
