# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/12 17:56:18 by msoria-j          #+#    #+#              #
#    Updated: 2023/03/31 14:32:29 by msoria-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm -f

NAME		=	libftprintf.a

SUBDIRS		=	libft

SRCS		=	ft_fprintf.c \
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
