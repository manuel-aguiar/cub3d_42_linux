/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 09:37:42 by marvin            #+#    #+#             */
/*   Updated: 2024/02/16 09:37:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_memfunc.h"

void	*ft_memdup(void *src, int bytes)
{
	void	*new;

	new = malloc(bytes);
	if (new)
		ft_memcpy(new, src, bytes);
	return (new);
}
