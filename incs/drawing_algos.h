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
# include "render_windows.h"
# include "vector.h"
# include "pixel_point.h"

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
}	t_lbclip;

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

typedef struct s_bh_line
{
	int x1;
	int x2;
	int y1;
	int y2;
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int	err_2;
}	t_bh_line;

//liang barsky
int		liang_barsky_clipper(t_pixel low_bot, t_pixel hi_top, t_pixel start, t_pixel end, t_pixel new[]);
float	lb_maxi(float arr[], int n);
float	lb_mini(float arr[], int n);

//xiaolin_wu.c
int		xiaolinwu_line(t_win *win, t_pixel start, t_pixel end);

//drawing lines.c
void	draw_horizontal_line(t_win *win, int min_x, int max_x, int y, int color);
void	draw_vertical_line(t_win *win, int start_y, int end_y, int x, int color);

void 	bersenham_line(t_win *win, t_pixel start, t_pixel end, int color);

#endif