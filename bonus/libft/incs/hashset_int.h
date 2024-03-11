/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashset_int.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:38:49 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/05/31 18:38:49 by mmaria-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHSET_INT_H

# define HASHSET_INT_H

# include <stdlib.h>

# include "int_sl_list.h"
# include "ft_memfunc.h"
# include "ft_math.h"
# include "error_handling.h"

typedef struct s_ihs_table
{
	int			*data;
	int			size;
	int			zero;
	t_ismlist	**collision;
}	t_ihs_table;

t_ihs_table	*ihs_init_table(int size);
int			ihs_hash_function(int key, int tab_size);
int			ihs_contains(t_ihs_table *table, int key);
int			ihs_insert(t_ihs_table *table, int key);
int			ihs_remove(t_ihs_table *table, int key);
void		ihs_table_print(t_ihs_table *table, void (*pnt)(int));
void		ihs_free_table(t_ihs_table **table);

/* escrever uma função para printar a tabela*/

#endif
