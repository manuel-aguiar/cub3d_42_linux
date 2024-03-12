/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perror_msg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:57:37 by codespace         #+#    #+#             */
/*   Updated: 2024/03/12 11:48:00 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error_handling.h"
#include "ft_printf.h"

int	error_msg_int(char *text, int print_to_this_fd, int number_to_return)
{
	ft_printf_fd(print_to_this_fd, "%s", "Error\n");
	ft_printf_fd(print_to_this_fd, "%s", text);
	return (number_to_return);
}

void	*error_msg_ptr(char *text, int print_to_this_fd, void *ptr_to_return)
{
	ft_printf_fd(print_to_this_fd, "%s", "Error\n");
	ft_printf_fd(print_to_this_fd, "%s", text);
	return (ptr_to_return);
}

void	error_msg_void(char *text, int print_to_this_fd)
{
	ft_printf_fd(print_to_this_fd, "%s", "Error\n");
	ft_printf_fd(print_to_this_fd, "%s", text);
}
