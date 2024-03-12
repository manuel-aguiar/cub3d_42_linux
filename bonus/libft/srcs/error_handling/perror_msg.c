/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:36:13 by mmaria-d          #+#    #+#             */
/*   Updated: 2024/03/12 11:29:36 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handling.h"
#include "ft_printf.h"

int	perror_msg_int(char *text, int number_to_return)
{
	perror(text);
	return (number_to_return);
}

void	*perror_msg_ptr(char *text, void *ptr_to_return)
{
	perror(text);
	return (ptr_to_return);
}

void	perror_msg_void(char *text)
{
	perror(text);
}
