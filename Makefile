# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 16:14:08 by msoria-j          #+#    #+#              #
#    Updated: 2023/03/31 14:32:29 by msoria-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

CC			=	gcc

SRCS		=	main.c \
				pipex.c \
				ft_split_args.c \
				ft_utils.c \

CFLAGS		=	-Wall -Werror -Wextra

OBJS		=	$(SRCS:.c=.o)

SUBDIRS		=	ft_fprintf

ft_fprintf	=	$(SUBDIRS)/libftprintf.a

ifndef VERBOSE
#	MAKEFLAGS += --silent
	MAKEFLAGS += --no-print-directory
endif

									  
$(NAME):		$(OBJS)
				@make -C $(SUBDIRS)
#				mv $(ft_fprintf)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(ft_fprintf)

all:			$(NAME)

clean:
				@make clean -C $(SUBDIRS)
				@$(RM) $(OBJS)

fclean:			clean
				@make fclean -C $(SUBDIRS)
				@$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re