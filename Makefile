# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 16:14:08 by msoria-j          #+#    #+#              #
#    Updated: 2023/03/10 16:34:53 by msoria-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	pipex

CC			=	gcc

SRCS		=	main.c \
#			ft_pipex.c \

CFLAGS		=	-Wall -Werror -Wextra

OBJS		=	$(SRCS:.c=.o)

SUBDIRS		=	ft_printf

FT_PRINTF	=	$(SUBDIRS)/libftprintf.a

$(NAME):		$(OBJS)
				@make -C $(SUBDIRS)
#				mv $(FT_PRINTF)
				$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(FT_PRINTF)

all:			$(NAME)

clean:
				@make clean -C $(SUBDIRS)
				$(RM) $(OBJS)

fclean:			clean
				@make fclean -C $(SUBDIRS)
				$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re