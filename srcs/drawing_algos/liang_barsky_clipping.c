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

#include "drawing_algos.h"

static void	lb_safety(t_pixel low_bot, t_pixel hi_top, \
	t_pixel *start, t_pixel *end)
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

static void	lb_ratios1(t_lbclip *lb)
{
	if (lb->p1 != 0)
	{
		lb->r1 = (float)lb->q1 / (float)lb->p1;
		lb->r2 = (float)lb->q2 / (float)lb->p2;
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
		lb->r3 = (float)lb->q3 / (float)lb->p3;
		lb->r4 = (float)lb->q4 / (float)lb->p4;
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

static int	lb_setup(t_pixel low_bot, t_pixel hi_top, \
	t_lbclip *lb, t_pixel *start, t_pixel *end)
{
	lb->p1 = -(end->x - start->x);
	lb->p2 = -lb->p1;
	lb->p3 = -(end->y - start->y);
	lb->p4 = -lb->p3;
	lb->q1 = start->x - low_bot.x;
	lb->q2 = hi_top.x - 1 - start->x;
	lb->q3 = start->y - low_bot.y;
	lb->q4 = hi_top.y - 1 - start->y;
	lb->posind = 1;
	lb->negind = 1;
	lb->posarr[0] = 1;
	lb->negarr[0] = 0;
	if ((lb->p1 == 0 && lb->q1 < 0) || (lb->p2 == 0 && lb->q2 < 0) || \
		(lb->p3 == 0 && lb->q3 < 0) || (lb->p4 == 0 && lb->q4 < 0))
		return (0);
	return (1);
}

int	liang_barsky_clipper(t_pixel low_bot, t_pixel hi_top, \
	t_pixel start, t_pixel end, t_pixel new[])
{
	t_lbclip	lb;

	if (!lb_setup(low_bot, hi_top, &lb, &start, &end))
		return (0);
	lb_ratios1(&lb);
	lb_ratios2(&lb);
	lb.rn1 = lb_maxi(lb.negarr, lb.negind);
	lb.rn2 = lb_mini(lb.posarr, lb.posind);
	if (lb.rn1 > lb.rn2)
		return (0);
	lb.xn1 = start.x + lb.p2 * lb.rn1;
	lb.yn1 = start.y + lb.p4 * lb.rn1;
	lb.xn2 = start.x + lb.p2 * lb.rn2;
	lb.yn2 = start.y + lb.p4 * lb.rn2;
	start.x = lb.xn1;
	start.y = lb.yn1;
	end.x = lb.xn2;
	end.y = lb.yn2;
	lb_safety(low_bot, hi_top, &start, &end);
	new[0] = start;
	new[1] = end;
	return (1);
}

