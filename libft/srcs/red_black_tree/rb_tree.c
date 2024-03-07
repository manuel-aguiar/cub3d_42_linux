/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 17:19:17 by marvin            #+#    #+#             */
/*   Updated: 2024/02/06 17:19:17 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "red_black_tree.h"

t_rb_node	*rbnode_new(void *data)
{
	t_rb_node	*node;

	node = malloc(sizeof(*node));
	if (!node)
		return (perror_msg_ptr("malloc", NULL));
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->color = RB_RED;
	node->data = data;
	return (node);
}

t_rb_tree	*rbtree_new(int (*comp)(void *, void *), void (*del)(void *))
{
	t_rb_tree	*tree;

	tree = malloc(sizeof(*tree));
	if (!tree)
		return (perror_msg_ptr("malloc", NULL));
	tree->head = NULL;
	tree->null = NULL;
	tree->members = 0;
	tree->levels = 0;
	tree->comp = comp;
	tree->del = del;
	return (tree);
}
