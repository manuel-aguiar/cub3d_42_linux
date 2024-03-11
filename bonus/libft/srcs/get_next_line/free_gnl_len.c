/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_gnl_len.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 11:47:31 by marvin            #+#    #+#             */
/*   Updated: 2024/01/12 11:47:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	free_gnl_len(void *gnl)
{
	t_gnl_len	*stack_gnl;

	stack_gnl = (t_gnl_len *)gnl;
	free(stack_gnl->line);
	free(stack_gnl);
}
