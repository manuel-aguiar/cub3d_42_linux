/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 16:57:37 by codespace         #+#    #+#             */
/*   Updated: 2024/03/12 12:36:45 by mmaria-d         ###   ########.fr       */
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
