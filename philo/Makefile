# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: miteixei <miteixei@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/30 19:51:28 by miteixei          #+#    #+#              #
#    Updated: 2025/03/30 20:52:53 by miteixei         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

$(CC) = cc

SRC = free.c init1.c init2.c input.c main.c \
	  monitor_utils1.c monitor_utils2.c philo.c philo_manners.c

OBJ = free.o init1.o init2.o input.o main.o \
	  monitor_utils1.o monitor_utils2.o philo.o philo_manners.o

NAME = philo

$(NAME): $(SRC) $(OBJ) philo.h
	$(CC) -Wall -Werror -Wextra -O3 -o $(NAME) $(OBJ)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean $(NAME)

all: $(NAME) clean

.PHONY: clean fclean all re
