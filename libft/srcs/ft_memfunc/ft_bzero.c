/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 13:58:28 by marvin            #+#    #+#             */
/*   Updated: 2023/03/11 13:58:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/* bzero sets the number of BYTES to zero starting at destination s
works with BYTES, so the caller must do the math in case s is an array
of something not a "char", using sizeof for example
same as calling memset (which also sets bytes) with constant '0'
for the same number of bytes.*/

#include "ft_memfunc.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, '\0', n);
}
