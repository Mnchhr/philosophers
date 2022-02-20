# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/11 14:21:27 by mkuehl            #+#    #+#              #
#    Updated: 2022/01/11 14:22:35 by mkuehl           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo_bonus
SRCS	= algo_bonus.c atoi_bonus.c main_bonus.c sem_bonus.c utils_bonus.c
CC	= gcc
CFLAGS 	= -Wall -Wextra -Werror
OBJS	:= $(SRCS:.c=.o)
HEADER	= philo_bonus.h

.PHONY: all clean fclean re bonus

all: $(NAME)

%.o: %.c $(HEADER)
	@$(CC) -c $(CFLAGS) -I $(HEADER) $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@rm -rf $(OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

bonus:	re