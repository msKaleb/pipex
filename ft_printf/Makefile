# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoria-j <msoria-j@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 17:56:18 by msoria-j          #+#    #+#              #
#    Updated: 2023/01/07 17:08:47 by msoria-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm -f

NAME		=	libftprintf.a

SUBDIRS		=	libft

SRCS		=	ft_printf.c \
				change_base.c \
				print_var.c \
				ft_itoa_u.c

OBJS		=	$(SRCS:.c=.o)


$(NAME):		$(OBJS)
				@make -C $(SUBDIRS)
				@mv $(SUBDIRS)/libft.a $(NAME)
				@ar rcs $(NAME) $(OBJS)

all:			$(NAME)

clean:
				@make clean -C $(SUBDIRS)
				@$(RM) $(OBJS)

fclean:			clean
				@make fclean -C $(SUBDIRS)
				@$(RM) $(NAME)

re:				fclean $(NAME)

.PHONY:			all clean fclean re
