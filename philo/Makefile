# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ghovhann <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/20 13:48:39 by ghovhann          #+#    #+#              #
#    Updated: 2021/07/20 13:48:42 by ghovhann         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBS = -lpthread

all:	$(NAME)

$(NAME):	$(OBJ)
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) ${LIBS}

clean:
			rm -rf $(OBJ)

fclean:		clean
			rm $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
