/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+
	+:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+
	+#+        */
/*                                                +#+#+#+#+#+
	+#+           */
/*   Created: 2023/04/18 17:46:11 by marvin            #+#    #+#             */
/*   Updated: 2023/04/18 17:46:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OUTPUT_H

# define FT_OUTPUT_H

# include "ft_printf.h"
# include "ft_string.h"
# include <unistd.h>

/* to print to standard output*/
int		ft_putchar(char c);
int		ft_putendl(char *str);
int		ft_putnbr(int nb);
int		ft_putstr(char *str);

/* to print to target fd*/
int		ft_putchar_fd(char c, int fd);
int		ft_putendl_fd(char *str, int fd);
int		ft_putnbr_fd(int nb, int fd);
int		ft_putstr_fd(char *str, int fd);

void	ft_print_arr(int *arr, int size, void (*pnt)(int));

#endif
