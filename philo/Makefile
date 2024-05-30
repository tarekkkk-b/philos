# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 13:57:28 by tarekkkk          #+#    #+#              #
#    Updated: 2024/05/27 20:15:20 by tabadawi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRCS = philo.c utils.c utils2.c parsing.c structs.c routine.c forks.c

CC = cc

CFLAGS = -Wall -Wextra -Werror #-fsanitize=address -g3

OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lpthread -o $(NAME)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)
	
re : fclean all

.PHONY	: all clean fclean re