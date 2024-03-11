/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: manuel <manuel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 15:32:04 by manuel            #+#    #+#             */
/*   Updated: 2023/03/11 15:32:04 by manuel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_output.h"

int	ft_putstr_fd(char *str, int fd)
{
	if (!*str || !str)
		return (0);
	return (write(fd, str, ft_strlen(str)));
}

int	ft_putstr(char *str)
{
	return (ft_putstr_fd(str, 1));
}
