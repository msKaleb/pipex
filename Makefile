# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msoria-j < msoria-j@student.42urduliz.c    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/10 16:14:08 by msoria-j          #+#    #+#              #
#    Updated: 2023/04/10 08:13:17 by msoria-j         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

define HEADER

██████╗ ██╗██████╗ ███████╗██╗  ██╗
██╔══██╗██║██╔══██╗██╔════╝╚██╗██╔╝
██████╔╝██║██████╔╝█████╗   ╚███╔╝ 
██╔═══╝ ██║██╔═══╝ ██╔══╝   ██╔██╗ 
██║     ██║██║     ███████╗██╔╝ ██╗
╚═╝     ╚═╝╚═╝     ╚══════╝╚═╝  ╚═╝

endef
export HEADER

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

#Define colors for output
NONE='\033[0m'
GREEN='\033[32m'
GRAY='\033[2;37m'
RED='\033[31m'
CYAN='\033[36m'
MAGENTA="\033[35m"
BLUE="\033[34m"
ITALIC="\033[3m"

ifndef VERBOSE
	MAKEFLAGS += --silent
#	MAKEFLAGS += --no-print-directory
endif

									  
$(NAME):		$(OBJS)
				@echo -e $(CYAN) "$$HEADER" $(NONE)
				@echo -e $(GREEN)$(ITALIC) "	Compiling $(NAME)..."$(NONE)
				@make -sC $(SUBDIRS)
				@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(ft_fprintf)

all:			$(NAME)

clean:
				@echo -e $(RED)$(ITALIC) "	cleaning $(NAME) object files..." $(NONE)
				@make clean -sC $(SUBDIRS)
				@$(RM) $(OBJS) $(BOBJS)

fclean:			clean
				@echo -e $(RED)$(ITALIC) "	removing $(NAME) file..." $(NONE)
				@make fclean -sC $(SUBDIRS)
				@$(RM) $(NAME)

re:				fclean $(NAME)

rebonus:		fclean bonus

bonus:			$(BOBJS)
				@echo -e $(BLUE) "$$HEADER" $(NONE)
				@echo -e $(MAGENTA)$(ITALIC) "	Compiling $(NAME) (Bonus)..."$(NONE)
				@make -sC $(SUBDIRS)
				@$(CC) $(CFLAGS) -o $(NAME) $(BOBJS) $(ft_fprintf)
				
.PHONY:			all clean fclean re bonus