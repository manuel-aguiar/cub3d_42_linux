/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ternary.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 18:16:28 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/09/24 14:23:50 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_math.h"

int	ft_ternary(int cond, int ret_true, int ret_false)
{
	if (cond)
		return (ret_true);
	return (ret_false);
}
