/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liang_barsky_clipping.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 13:45:24 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/11 13:45:24 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "drawing_algos.h"

float	lb_maxi(float arr[], int n);
float	lb_mini(float arr[], int n);

static void	lb_ratios1(t_lbclip *lb)
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

static void	lb_ratios2(t_lbclip *lb)
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

static int	lb_setup(t_lbclip *lb)
{
	lb->p1 = -(lb->line[1].x - lb->line[0].x);
	lb->p2 = -lb->p1;
	lb->p3 = -(lb->line[1].y - lb->line[0].y);
	lb->p4 = -lb->p3;
	lb->q1 = lb->line[0].x - lb->box[0].x;
	lb->q2 = lb->box[1].x - lb->line[0].x;
	lb->q3 = lb->line[0].y - lb->box[0].y;
	lb->q4 = lb->box[1].y - lb->line[0].y;
	lb->posind = 1;
	lb->negind = 1;
	lb->posarr[0] = 1;
	lb->negarr[0] = 0;
	if ((lb->p1 == 0 && lb->q1 < 0) || (lb->p2 == 0 && lb->q2 < 0) || \
		(lb->p3 == 0 && lb->q3 < 0) || (lb->p4 == 0 && lb->q4 < 0))
		return (0);
	return (1);
}

int	liang_barsky_clipping(t_pixel win[2], t_pixel draw[2], t_pixel res[2])
{
	t_lbclip	lb;

	lb.box[0] = win[0];
	lb.box[1] = win[1];
	lb.line[0] = draw[0];
	lb.line[1] = draw[1];
	if (!lb_setup(&lb))
		return (0);
	lb_ratios1(&lb);
	lb_ratios2(&lb);
	lb.rn1 = lb_maxi(lb.negarr, lb.negind);
	lb.rn2 = lb_mini(lb.posarr, lb.posind);
	if (lb.rn1 > lb.rn2)
		return (0);
	lb.xn1 = lb.line[0].x + lb.p2 * lb.rn1;
	lb.yn1 = lb.line[0].y + lb.p4 * lb.rn1;
	lb.xn2 = lb.line[0].x + lb.p2 * lb.rn2;
	lb.yn2 = lb.line[0].y + lb.p4 * lb.rn2;
	lb.line[0].x = lb.xn1;
	lb.line[0].y = lb.yn1;
	lb.line[1].x = lb.xn2;
	lb.line[1].y = lb.yn2;
	res[0] = lb.line[0];
	res[1] = lb.line[1];
	return (1);
}
