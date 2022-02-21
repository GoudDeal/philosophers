# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcyprien <dcyprien@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/08/18 19:51:49 by dcyprien          #+#    #+#              #
#    Updated: 2022/02/16 20:12:47 by dcyprien         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	./srcs/philosophers.c\
			./srcs/ft_atoi.c\
			./srcs/initialisation.c\
			./srcs/ft_isdigit.c\
			./srcs/philo_utils.c\
			./srcs/thread_handling.c\
			./srcs/routine.c\
			./srcs/action.c\
			./srcs/free_unlock.c\
			./srcs/action_utils.c\
			./srcs/forks_utils.c\
			./srcs/ft_itoa.c


NAME	=	philo

CC		=	cc 

CFLAGS	=	-Wall -Wextra -Werror -g3

OBJS	=	${SRCS:.c=.o}

OBJSBONUS	=	${SRCSBONUS:.c=.o}

RM		=	rm -f


$(NAME):	${OBJS}
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} -lpthread

all:		${NAME}

clean:		
	${RM} ${OBJS} ${OBJSBONUS}

fclean:		clean
	${RM} ${NAME}

re:			fclean all

.PHONY = all clean fclean re

