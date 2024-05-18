# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tarekkkk <tarekkkk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/18 18:45:07 by tarekkkk          #+#    #+#              #
#    Updated: 2024/05/18 18:51:33 by tarekkkk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philos.c	parsing.c routine.c time.c

CC = cc

CFLAGS = -Wall -Wextra -Werror

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)
	
re : fclean all

.PHONY	: all clean fclean re