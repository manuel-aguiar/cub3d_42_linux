# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmaria-d <mmaria-d@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/11 21:17:52 by mmaria-d          #+#    #+#              #
#    Updated: 2024/03/12 10:12:38 by mmaria-d         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3D

all:		$(NAME)

$(NAME):
		make -C ./mandatory
clean:
			make clean -C ./mandatory
			make clean -C ./bonus

fclean:		clean
			make fclean -C ./mandatory
			make fclean -C ./bonus

bonus:
		make -C ./bonus

re:	fclean 
	make all

git: fclean
	git add * && git commit -m "commiting" && git push

.PHONY: all clean fclean re bonus git