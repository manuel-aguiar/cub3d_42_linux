/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_detection.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 09:15:13 by marvin            #+#    #+#             */
/*   Updated: 2024/02/24 09:15:13 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HIT_DETECTION_H

# define HIT_DETECTION_H

# include "libft.h"
# include "vector.h"

typedef struct s_hitnode	t_hitnode;
typedef struct s_sprite		t_sprite;

//hitnode and list, linked list for map collisions
typedef struct s_hitnode
{
	t_sprite	*sprite;
	t_hitnode	*next;
	t_hitnode	*prev;
}	t_hitnode;

typedef struct s_hitlist
{
	t_hitnode	*head;
	t_hitnode	*tail;
	size_t		len;
}	t_hitlist;

//liang barsky struct for collisions
typedef struct s_lb_hit
{
	float		p1;
	float		p2;
	float		p3;
	float		p4;
	float		q1;
	float		q2;
	float		q3;
	float		q4;
	float		posarr[5];
	float		negarr[5];
	int			posind;
	int			negind;
	float		r1;
	float		r2;
	float		r3;
	float		r4;
	float		xn1;
	float		yn1;
	float		xn2;
	float		yn2;
	float		rn1;
	float		rn2;
	t_vec2d		box[2];
	t_vec2d		line[2];
}	t_lb_hit;

int		liang_barsky_hit(t_vec2d *win, t_vec2d *draw, t_vec2d *res);
void	hitlist_in_head(t_hitlist *list, t_hitnode *insert);
void	hitlist_in_tail(t_hitlist *list, t_hitnode *insert);
void	hitlist_del_head(t_hitlist *list);
void	hitlist_del_tail(t_hitlist *list);

#endif
