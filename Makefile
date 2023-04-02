# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 16:14:08 by msoria-j          #+#    #+#              #
#    Updated: 2023/04/02 14:37:52 by msoria-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

CC			=	gcc

SRCS		=	main.c \
				pipex.c \
				ft_split_args.c \
				ft_utils.c \

BONUS		=	main_bonus.c \
				pipex_bonus.c \
				ft_split_args_bonus.c \
				ft_utils_bonus.c \
				
CFLAGS		=	-Wall -Werror -Wextra

OBJS		=	$(SRCS:.c=.o)

BOBJS		=	$(BONUS:.c=.o)

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
				@$(RM) $(OBJS) $(BOBJS)

fclean:			clean
				@make fclean -C $(SUBDIRS)
				@$(RM) $(NAME)

re:				fclean $(NAME)

bonus:			$(BOBJS)
				@make -C $(SUBDIRS)
				@$(CC) $(CFLAGS) -o $(NAME) $(BOBJS) $(ft_fprintf)
				
.PHONY:			all clean fclean re