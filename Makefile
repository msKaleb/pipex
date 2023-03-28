# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 16:14:08 by msoria-j          #+#    #+#              #
#    Updated: 2023/03/28 12:28:04 by msoria-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

CC			=	gcc

SRCS		=	main.c \
				ft_split_args.c \

CFLAGS		=	-Wall -Werror -Wextra

OBJS		=	$(SRCS:.c=.o)

SUBDIRS		=	ft_printf

FT_PRINTF	=	$(SUBDIRS)/libftprintf.a

ifndef VERBOSE
#	MAKEFLAGS += --silent
	MAKEFLAGS += --no-print-directory
endif

									  
$(NAME):		$(OBJS)
				@make -C $(SUBDIRS)
#				mv $(FT_PRINTF)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(FT_PRINTF)

all:			$(NAME)

clean:
				@make clean -C $(SUBDIRS)
				@$(RM) $(OBJS)

fclean:			clean
				@make fclean -C $(SUBDIRS)
				@$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re