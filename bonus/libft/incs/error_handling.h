/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 12:33:20 by mmaria-d          #+#    #+#             */
/*   Updated: 2023/09/19 17:00:21 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_HANDLING_H

# define ERROR_HANDLING_H

# include <errno.h>
# include <stdio.h>

int		error_msg_int(char *text, int print_to_this_fd, int number_to_return);
void	*error_msg_ptr(char *text, int print_to_this_fd, void *ptr_to_return);
void	error_msg_void(char *text, int print_to_this_fd);
int		perror_msg_int(char *text, int number_to_return);
void	*perror_msg_ptr(char *text, void *ptr_to_return);
void	perror_msg_void(char *text);

#endif
