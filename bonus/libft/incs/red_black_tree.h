/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_black_tree.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:11:15 by marvin            #+#    #+#             */
/*   Updated: 2024/02/06 17:11:15 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RED_BLACK_TREE_H

# define RED_BLACK_TREE_H

# include <stdlib.h>
# include <stdint.h>
# include <stddef.h>
# include "ft_memfunc.h"
# include "error_handling.h"

# define RB_RED 114
# define RB_BLACK 98

/* can use memory pool as linkedlist to guarantee locality*/

typedef struct s_rb_node	t_rb_node;
typedef struct s_rb_tree	t_rb_tree;

struct s_rb_node
{
	void		*data;
	char		color;
	t_rb_node	*parent;
	t_rb_node	*left;
	t_rb_node	*right;
};

struct s_rb_tree
{
	t_rb_node	*head;
	t_rb_node	*null;
	size_t		members;
	size_t		levels;
	int			(*comp)(void *, void *);
	void		(*del)(void *);
};

t_rb_tree	*rbtree_new(int (*comp)(void *, void *), void (*del)(void *));
t_rb_node	*rbnode_new(void *data);

#endif
