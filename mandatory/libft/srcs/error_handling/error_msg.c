/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:36:13 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/09/19 16:58:26 by codespace        ###   ########.fr       */
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
