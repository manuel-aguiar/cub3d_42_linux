/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:26:44 by manuel            #+#    #+#             */
/*   Updated: 2023/09/23 15:15:58 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_output.h"

int	ft_putchar_fd(char c, int fd)
{
	return (write(fd, &c, 1));
}

int	ft_putchar(char c)
{
	return (ft_putchar_fd(c, 1));
}
