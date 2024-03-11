/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_linkedlists.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:07:43 by marvin            #+#    #+#             */
/*   Updated: 2023/09/20 11:16:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HT_LINKEDLISTS_H

# define HT_LINKEDLISTS_H

# include "error_handling.h"
# include "ft_memfunc.h"
# include <stdint.h>
# include <stdlib.h>

typedef struct s_htnode
{
	void			*key;
	void			*value;
	struct s_htnode	*next;
	struct s_htnode	*prev;
}					t_htnode;

typedef struct s_htlist
{
	t_htnode		*head;
	t_htnode		*tail;
	size_t			len;
}					t_htlist;

t_htlist			*htlist_new(void);
int					htlist_in_head(t_htlist *list, void *key, void *value);
int					htlist_in_tail(t_htlist *list, void *key, void *value);
int					htlist_find(t_htlist *list, void *key, int (*cmp)(void *,
							void *));
void				htlist_remove_if(t_htlist *list, void *key,
						int (*cmp)(void *, void *), void (*del)(void *));
void				htlist_del_pair(t_htlist *list, t_htnode *node,
						void (*del_key)(void *), void (*del_value)(void *));
void				htlist_head_print(t_htlist *list, void (*pnt)(void *));
void				htlist_tail_print(t_htlist *list, void (*pnt)(void *));
void				htlist_destroy(t_htlist **list, void (*del_key)(void *),
						void (*del_value)(void *));

#endif
