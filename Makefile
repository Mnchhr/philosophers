# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkuehl <mkuehl@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/21 16:13:45 by mkuehl            #+#    #+#              #
#    Updated: 2022/01/11 14:22:21 by mkuehl           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 	= philo
SRCS	= algo.c atoi.c main.c threads.c utils.c
CC	= gcc
CFLAGS 	= -Wall -Wextra -Werror
OBJS	:= $(SRCS:.c=.o)
HEADER	= philo.h

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