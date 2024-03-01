/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_lb_clipping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/14 14:32:18 by marvin            #+#    #+#             */
/*   Updated: 2023/08/14 14:32:18 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hit_detection.h"

/*

static void	lb_safety(t_vec2d low_bot, t_vec2d hi_top, t_vec2d *start, t_vec2d *end)
{
	if (start->x > hi_top.x - 1)
		start->x = hi_top.x - 1;
	if (start->x < low_bot.x)
		start->x = low_bot.x;
	if (start->y > hi_top.y - 1)
		start->y = hi_top.y - 1;
	if (start->y < low_bot.y)
		start->y = low_bot.y;
	if (end->x > hi_top.x - 1)
		end->x = hi_top.x - 1;
	if (end->x < low_bot.x)
		end->x = low_bot.x;
	if (end->y > hi_top.y - 1)
		end->y = hi_top.y - 1;
	if (end->y < low_bot.y)
		end->y = low_bot.y;
}

*/


float	lb_hit_maxi(float arr[], int n);
float	lb_hit_mini(float arr[], int n);



static void	lb_ratios1(t_lb_hit *lb)
{
	if (lb->p1 != 0)
	{
		lb->r1 = lb->q1 / lb->p1;
		lb->r2 = lb->q2 / lb->p2;
		if (lb->p1 < 0)
		{
			lb->negarr[lb->negind++] = lb->r1;
			lb->posarr[lb->posind++] = lb->r2;
		}
		else
		{
			lb->negarr[lb->negind++] = lb->r2;
			lb->posarr[lb->posind++] = lb->r1;
		}
	}
}

static void	lb_ratios2(t_lb_hit *lb)
{
	if (lb->p3 != 0)
	{
		lb->r3 = lb->q3 / lb->p3;
		lb->r4 = lb->q4 / lb->p4;
		if (lb->p3 < 0)
		{
			lb->negarr[lb->negind++] = lb->r3;
			lb->posarr[lb->posind++] = lb->r4;
		}
		else
		{
			lb->negarr[lb->negind++] = lb->r4;
			lb->posarr[lb->posind++] = lb->r3;
		}
	}
}

static int	lb_setup(t_vec2d low_bot, t_vec2d hi_top, t_lb_hit *lb, t_vec2d *start, t_vec2d *end)
{
	lb->p1 = -(end->x - start->x);
	lb->p2 = -lb->p1;
	lb->p3 = -(end->y - start->y);
	lb->p4 = -lb->p3;
	lb->q1 = start->x - low_bot.x;
	lb->q2 = hi_top.x - start->x;
	lb->q3 = start->y - low_bot.y;
	lb->q4 = hi_top.y - start->y;
	lb->posind = 1;
	lb->negind = 1;
	lb->posarr[0] = 1;
	lb->negarr[0] = 0;
	if ((lb->p1 == 0 && lb->q1 < 0) || (lb->p2 == 0 && lb->q2 < 0) || \
		(lb->p3 == 0 && lb->q3 < 0) || (lb->p4 == 0 && lb->q4 < 0))
		return (0);
	return (1);
}

int	liang_barsky_hit(t_vec2d win[2], t_vec2d draw[2], t_vec2d res[2])
{
	t_lb_hit	lb;
	t_vec2d box[2];
	t_vec2d line[2];

	box[0] = win[0];
	box[1] = win[1];
	line[0] = draw[0];
	line[1] = draw[1];
	if (!lb_setup(box[0], box[1], &lb, &line[0], &line[1]))
		return (0);
	lb_ratios1(&lb);
	lb_ratios2(&lb);
	lb.rn1 = lb_hit_maxi(lb.negarr, lb.negind);
	lb.rn2 = lb_hit_mini(lb.posarr, lb.posind);
	if (lb.rn1 > lb.rn2)
		return (0);
	lb.xn1 = line[0].x + lb.p2 * lb.rn1;
	lb.yn1 = line[0].y + lb.p4 * lb.rn1;
	lb.xn2 = line[0].x + lb.p2 * lb.rn2;
	lb.yn2 = line[0].y + lb.p4 * lb.rn2;
	line[0].x = lb.xn1;
	line[0].y = lb.yn1;
	line[1].x = lb.xn2;
	line[1].y = lb.yn2;
	res[0] = line[0];
	res[1] = line[1];
	return (1);
}

